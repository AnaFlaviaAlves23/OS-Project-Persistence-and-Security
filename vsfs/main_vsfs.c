#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "vsfs_format.h"
#include "vsfs_control.h"

void SimplesOS(){
    printf("==================================================\n");
    printf("\033[1;36m");
    printf("  ____  _                 _        ___  ____  \n");
    printf(" / ___|| |__ __  _ __    | |  ___ / _ \\/ ___| \n");
    printf(" \\___ \\| | '_ ` _ \\| '_ \\| | / _ \\ | | \\___ \\ \n");
    printf("  ___) | | | | | | | |_) | ||  __/ |_| |___) |\n");
    printf(" |____/|_|_| |_| |_| .__/|_| \\___|\\___/|____/ \n");
    printf("                   |_|                       \n");
    printf("\033[0m");
    printf("==================================================\n");
}

void ajuda() {
    printf("\n------------------ Comandos do Simulador vsfs ------------------------------\n");
    printf("format                      - Formata o disco virtual (disco.img)\n");
    printf("write <conteudo>            - Grava um novo arquivo com o conteudo digitado\n");
    printf("read <numero_do_inode>      - Le e exibe o conteudo contido no inode informado\n");
    printf("list                        - Lista todos os inodes ativos e seus metadados\n");
    printf("help                        - Mostra este menu de ajuda\n");
    printf("exit                        - Encerra o simulador\n");
    printf("----------------------------------------------------------------------------\n");
}

void loading_system() {
    printf("Inicializando o Micro Sistema de Arquivos vsfs");
    fflush(stdout);
    usleep(300000);

    printf(".");
    fflush(stdout);
    usleep(300000);

    printf(".");
    fflush(stdout);
    usleep(300000);

    printf(".\n");
    usleep(300000);
}

void shutdown_system() {
    printf("\n[Protocolo] Solicitacao de encerramento recebida ");

    for (int i = 0; i < 3; i++) {
        usleep(400000);
        printf(".");
        fflush(stdout);
    }
    usleep(400000);
    printf("\n");
    printf("Desconectando modulos logicos ");
    fflush(stdout); 
    
    for (int i = 0; i < 3; i++) {
        usleep(400000);
        printf(".");
        fflush(stdout);
    }
    printf("\033[H\033[J");
    usleep(300000);

    char banner[] = "---------------------SimpleOS------------------";
    int len = strlen(banner);
    
    int esquerda = 0;
    int direita = len - 1;

    printf("===============================================\n");
    printf("%s\n", banner);
    printf("===============================================\n");
    fflush(stdout);
    usleep(80000);

    while (esquerda <= direita) {
        printf("\033[3A");

        banner[esquerda] = '|';
        banner[direita] = '|';

        printf("===============================================\n");
        printf("%s\n", banner); 
        printf("===============================================\n");
        fflush(stdout);
        
        usleep(80000);
        
        esquerda++;
        direita--;
    }

    usleep(300000);

    printf("\033[H\033[J");
    
    printf("\033[1;36m");
    printf("\n     SimpleOS desligado com sucesso!\n");
    printf("                Até logo!\n");
    printf("                   =)\n\n");
    printf("\033[0m");

    usleep(2500000);
    printf("\033[H\033[J"); 
}

int main(){
    char input[512];
    char command[64];
    char argument[448];

    system("clear");
    SimplesOS();
    loading_system();
    ajuda();

    while (1) {
        printf("\nvsfs_shell> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL)  {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) continue;

        memset(command, 0, sizeof(command));
        memset(argument, 0, sizeof(argument));

        char *space = strchr(input, ' ');
        if (space != NULL) {
            strncpy(command, input, space - input);
            strcpy(argument, space + 1);
        } else {
            strcpy(command, input);
        }

        if (strcmp(command, "exit") == 0) {
            shutdown_system();
            break;
        } 
        else if (strcmp(command, "help") == 0) {
            ajuda();
        } 
        else if (strcmp(command, "format") == 0) {
            printf("[Executando] Formatando o disco virtual...\n");
            if (format_disk("disco.img") == 0) {
                printf("[Sucesso] Sistema de arquivos limpo criado em 'disco.img'.\n");
            } else {
                printf("[Erro] Falha ao tentar formatar o arquivo de disco.\n");
            }
        } 
        else if (strcmp(command, "write") == 0) {
            if (strlen(argument) == 0) {
                printf("[Erro] O comando 'write' exige um conteudo. Exemplo: write OlaMundo\n");
                continue;
            }
            printf("[Executando] Gravando dados informados via terminal...\n");
            write_file("disco.img", argument, strlen(argument) + 1);
        }
        else if (strcmp(command, "read") == 0) {
            if (strlen(argument) == 0) {
                printf("[Erro] O comando 'read' exige o numero do inode. Exemplo: read 0\n");
                continue;
            }
            int target_inode = atoi(argument);
            read_file("disco.img", target_inode);
        }
        else if (strcmp(command, "list") == 0) {
            list_inodes("disco.img");
        }
        else {
            printf("[Erro] Comando '%s' não reconhecido. Digite 'help' para listar comandos válidos.\n", command);
        }
    }

    return 0;
}