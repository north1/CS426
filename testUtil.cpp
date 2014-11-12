#include "utilities.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv) { 
    initOpenSSL();
    
    printf("sizeof(time_t)=%i\n", (int)sizeof(time_t));

    unsigned char *key = random256(); 
    unsigned char *iv = random128(); 
    const char *plain = "please work, please work, please work, yes, please work, yes work!";

    unsigned char *plaintext = (unsigned char *)malloc(strlen(plain)+1);
    strcpy((char *)plaintext, (char *)plain);
    int plaintext_len = strlen((char *)plaintext);

    int ciphertext_len;
    unsigned char *ciphertext = 
        (unsigned char *)encryptAES(plaintext, plaintext_len, key, iv, &ciphertext_len); 

    printf("plaintext length is %i ciphertext length is %i\n", plaintext_len, ciphertext_len); 

    plaintext = 
        (unsigned char *)decryptAES(ciphertext, ciphertext_len, key, iv, &plaintext_len); 
    plaintext[plaintext_len] = 0; 

    printf("plaintext length is %i ciphertext length is %i\n", plaintext_len, ciphertext_len); 
    printf("plaintext is <%s>\n", plaintext);
}
