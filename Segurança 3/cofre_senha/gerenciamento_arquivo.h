#ifndef GERENCIAMENTO_ARQUIVO_H
#define GERENCIAMENTO_ARQUIVO_H

#include "modulo_autenticacao.h"

#define MAX_ENTRIES 100
#define VAULT_FILE "cofre.bin"

typedef struct {
    char site[64];
    char username[64];
    char password[64];
} Entry;

typedef struct {
    unsigned char salt[SALT_LEN];
    unsigned char hash[32];
    int count;
    Entry entries[MAX_ENTRIES];
} Vault;

void save_vault(Vault* vault);
int load_vault(Vault* vault);

#endif