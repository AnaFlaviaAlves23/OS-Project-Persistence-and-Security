#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "modulo_autenticacao.h"

void generate_salt(unsigned char* salt) {
    RAND_bytes(salt, SALT_LEN);
}

void hash_password(const char* pass, const unsigned char* salt, unsigned char* out_hash) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, salt, SALT_LEN);
    EVP_DigestUpdate(ctx, pass, strlen(pass));
    EVP_DigestFinal_ex(ctx, out_hash, NULL);
    EVP_MD_CTX_free(ctx);
}