#include<stdio.h>
#include<string.h>
#include "vsfs.h"
#include "vsfs_format.h"

int format_disk(const char *filename){
    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    struct vsfs_disk disk;
    memset(&disk, 0, sizeof(struct vsfs_disk));

    disk.sb.magic = MAGIC_NUMBER;
    disk.sb.num_inodes = MAX_INODES;
    disk.sb.num_data_blocks = DISK_BLOCKS;

    fwrite(&disk, sizeof(struct vsfs_disk), 1, fp);
    fclose(fp);
    return 0;
}