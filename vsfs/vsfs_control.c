#include<stdio.h>
#include<string.h>
#include "vsfs.h"
#include "vsfs_control.h"

int find_free_bit(char *bitmap, int size){
    for(int i = 0; i < size; i++){
        if(bitmap[i] == 0){
            return i;
        }
    }
    return -1;
}

int write_file(const char *disk_name, char *data, int data_len){
    FILE *disk = fopen(disk_name, "rb+");
    if(disk == NULL){
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    struct vsfs_disk v_disk;
    fread(&v_disk, sizeof(struct vsfs_disk), 1, disk);

    int inode_idx = find_free_bit(v_disk.inode_bitmap, MAX_INODES);
    int data_idx = find_free_bit(v_disk.data_bitmap, DISK_BLOCKS);

    if(inode_idx == -1 || data_idx == -1){
        fprintf(stderr, "[ALERTA]: Espaco insuficiente no disco ou tabela de inodes cheia!\n");
        fclose(disk);
        return -1;
    }

    v_disk.inode_bitmap[inode_idx] = 1;
    v_disk.data_bitmap[data_idx] = 1;

    v_disk.inodes[inode_idx].size = data_len;
    v_disk.inodes[inode_idx].type = 1; 
    v_disk.inodes[inode_idx].direct = data_idx;

    memcpy(v_disk.data_blocks[data_idx], data, data_len);

    fseek(disk, 0, SEEK_SET);
    fwrite(&v_disk, sizeof(struct vsfs_disk), 1, disk);

    fclose(disk);

    printf("[SUCESSO]: Arquivo gravado com sucesso.\nInode: %d\nBloco de Dados: %d\n", inode_idx, data_idx);
    return 0;
}

int read_file(const char *disk_name, int inode_idx) {
    if (inode_idx < 0 || inode_idx >= MAX_INODES) {
        printf("[Erro] Indice de inode %d invalido. O limite do vsfs e de 0 a %d.\n", inode_idx, MAX_INODES - 1);
        return -1;
    }

    FILE *disk = fopen(disk_name, "rb");
    if (!disk) {
        printf("[Erro] O disco '%s' nao foi encontrado. Execute 'format' primeiro.\n", disk_name);
        return -1;
    }

    struct vsfs_disk v_disk;
    fread(&v_disk, sizeof(struct vsfs_disk), 1, disk);
    fclose(disk);

    if (v_disk.inode_bitmap[inode_idx] == 0) {
        printf("[Aviso] O Inode %d esta vazio. Nenhum arquivo armazenado.\n", inode_idx);
        return -1;
    }

    int bloco_dados = v_disk.inodes[inode_idx].direct;
    int tamanho_bytes = v_disk.inodes[inode_idx].size;

    printf("Lendo Inode %d\nTamanho: %d bytes\nApontando para o Bloco de Dados: %d\n", 
           inode_idx, tamanho_bytes, bloco_dados);
    
    printf("[Conteudo do Arquivo]: %s\n", v_disk.data_blocks[bloco_dados]);

    return 0;
}

void list_inodes(const char *disk_name) {
    FILE *disk = fopen(disk_name, "rb");
    if (!disk) {
        printf("[Erro] O disco '%s' nao foi encontrado. Execute 'format' primeiro.\n", disk_name);
        return;
    }

    struct vsfs_disk v_disk;
    fread(&v_disk, sizeof(struct vsfs_disk), 1, disk);
    fclose(disk);

    printf("\n================ TABELA DE INODES ATIVOS ================\n");
    printf("%-10s %-15s %-15s %-15s\n", "Inode ID", "Status", "Tamanho (Bytes)", "Bloco Direto");
    printf("--------------------------------------------------------\n");

    int ativos = 0;
    for (int i = 0; i < MAX_INODES; i++) {
        if (v_disk.inode_bitmap[i] == 1) {
            printf("%-10d %-15s %-15d %-10d\n", 
                   i, 
                   "EM USO", 
                   v_disk.inodes[i].size, 
                   v_disk.inodes[i].direct);
            ativos++;
        }
    }

    if (ativos == 0) {
        printf("Nenhum inode ativo no momento.\n");
    }
    printf("========================================================\n");
}