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

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

unsigned char * encryptAES(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, int*ciphertext_len) { 
  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */

  /* A 256 bit key */

  /* A 128 bit IV */
  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  unsigned char * ciphertext = (unsigned char *)malloc(plaintext_len+AES_BLOCK_SIZE-1);

  /* Encrypt the plaintext */
  *ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv,
    ciphertext);
  
  return ciphertext;

}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

unsigned char * decryptAES(unsigned char *ciphertext, int ciphertext_len,
        unsigned char *key, unsigned char *iv, int*plaintext_len) { 
  unsigned char * plaintext = (unsigned char *)malloc(ciphertext_len+AES_BLOCK_SIZE-1);
  *plaintext_len = decrypt(ciphertext, ciphertext_len, key, iv,
    plaintext);
  return plaintext; 
}


