#ifndef MODULO_AUTENTICACAO_H
#define MODULO_AUTENTICACAO_H

#define SALT_LEN 16

void generate_salt(unsigned char* salt);
void hash_password(const char* pass, const unsigned char* salt, unsigned char* out_hash);

#endif