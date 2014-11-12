#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <string.h>

unsigned char * random128();
unsigned char * random160();
unsigned char * random256();
void initOpenSSL();
//key is 256 bits
//iv is 128 bits

void ustrncpy(unsigned char *, unsigned char *, int);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext);
unsigned char * encryptAES(unsigned char* plaintext, int plaintext_len, 
        unsigned char* key, unsigned char* iv, int *ciphertext_len);
unsigned char * decryptAES(unsigned char* ciphertext, int ciphertext_len, 
        unsigned char* key, unsigned char* iv, int *plaintext_len);

