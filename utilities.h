#include <stdio.h>
#include <stdlib.h>

unsigned char * random128();
unsigned char * random160();
unsigned char * random256();
void initOpenSSL();
char * encryptAES(unsigned char* plaintext, int plaintext_len, unsigned char* key, unsigned char* iv, int ciphertext_len);
char * decryptAES(unsigned char* ciphertext, int ciphertext_len, unsigned char* key, unsigned char* iv, int plaintext_len);
