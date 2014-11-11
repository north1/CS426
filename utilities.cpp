#include "utilities.h"

unsigned char * random128() {
	unsigned char * ret = (unsigned char*) malloc(16); //16 bytes = 128 bits
	for (int i = 0; i < 16; i++) {
		ret[i] = (unsigned char)(rand()%256);	
	}
	return ret;
}

unsigned char * random160() {
	unsigned char * ret = (unsigned char*) malloc(20); //16 bytes = 128 bits
	for (int i = 0; i < 20; i++) {
		ret[i] = (unsigned char)(rand()%256);	
	}
	return ret;
}

unsigned char * random256() {
	unsigned char * ret = (unsigned char *) malloc(32); //32 bytes = 256 bits
	for (int i = 0; i < 32; i++) {
		ret[i] = (unsigned char)(rand()%256);
	}
	return ret;
}


void initOpenSSL() { 
  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);
}

char * encryptAES(unsigned char *plaintext, int plaintext_len, 
        unsigned char *key, unsigned char *iv, int*ciphertext_len) { 
  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */

  /* A 256 bit key */

  /* A 128 bit IV */
  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  unsigned char * ciphertext = (unsigned char *)malloc(size(unsigned char)*plaintext_len*2);

  /* Encrypt the plaintext */
  *ciphertext_len = encrypt(plaintext, strlen(plaintext), key, iv,
    ciphertext);
  
  return ciphertext;

}

char * decryptAES(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, int*plaintext_len) { 
  unsigned char * plaintext = (unsigned char *)malloc(size(unsigned char)*ciphertext_len*2);
  *plaintext_len = decrypt(ciphertext, ciphertext_len, key, iv,
    decryptedtext);
  return plaintext; 
}
