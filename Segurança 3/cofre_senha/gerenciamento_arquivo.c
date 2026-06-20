#include <stdio.h>
#include "gerenciamento_arquivo.h"

void save_vault(Vault* vault) {
    FILE* f = fopen(VAULT_FILE, "wb");
    fwrite(vault, sizeof(Vault), 1, f);
    fclose(f);
}

int load_vault(Vault* vault) {
    FILE* f = fopen(VAULT_FILE, "rb");
    if (!f) return 0;
    fread(vault, sizeof(Vault), 1, f);
    fclose(f);
    return 1;
}