#include <stdio.h>
#include <string.h>
#include "modulo_autenticacao.h"
#include "gerenciamento_arquivo.h"

int main() {
    char master_pass[128];
    Vault vault;
    unsigned char hash[32];

    printf("Cofre de Senhas\n");
    printf("Senha Principal: ");
    scanf("%127s", master_pass);

    if (!load_vault(&vault)) {
        printf("Criando novo cofre\n");
        generate_salt(vault.salt);
        hash_password(master_pass, vault.salt, vault.hash);
        vault.count = 0;
        save_vault(&vault);
    } else {
        hash_password(master_pass, vault.salt, hash);
        if (memcmp(hash, vault.hash, 32) != 0) {
            printf("Senha incorreta!\n");
            return 1;
        }
        printf("Cofre aberto. %d entrada(s).\n", vault.count);
    }

    int opcao;
    do {
        printf("\n1. Mostrar\n2. Adicionar\n0. Sair\nOpcao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        while (getchar() != '\n');

        if (opcao == 1) {
            for (int i = 0; i < vault.count; i++)
                printf("[%d] %s | %s | %s\n", i+1,
                    vault.entries[i].site,
                    vault.entries[i].username,
                    vault.entries[i].password);

        } else if (opcao == 2) {
            Entry* e = &vault.entries[vault.count];
            printf("Site: "); scanf("%63s", e->site);
            printf("Usuario: "); scanf("%63s", e->username);
            printf("Senha: "); scanf("%63s", e->password);
            vault.count++;
            save_vault(&vault);
            printf("Salvo!\n");
        }
    } while (opcao != 0);

    return 0;
}