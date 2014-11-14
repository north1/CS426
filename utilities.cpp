#include "utilities.h"

//Author Mike North
unsigned char * random128() {
	unsigned char * ret = (unsigned char*) malloc(16); //16 bytes = 128 bits
	for (int i = 0; i < 16; i++) {
		ret[i] = (unsigned char)(rand()%256);	
	}
	return ret;
}

//author Caleb Rouleau
unsigned char * random160() {
	unsigned char * ret = (unsigned char*) malloc(20); //16 bytes = 128 bits
	for (int i = 0; i < 20; i++) {
		ret[i] = (unsigned char)(rand()%256);	
	}
	return ret;
}

//Author Mike North
unsigned char * random256() {
	unsigned char * ret = (unsigned char *) malloc(32); //32 bytes = 256 bits
	for (int i = 0; i < 32; i++) {
		ret[i] = (unsigned char)(rand()%256);
	}
	return ret;
}

//Author Caleb Rouleau
void ustrncpy(unsigned char *dest, unsigned char *src, int n) { 
    for(int i = 0; i<n; i++) { 
        dest[i] = src[i]; 
    }
}

//Author: taken from internet http://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
void initOpenSSL() { 
  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);
}

//Author: taken from internet http://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

//Author: taken from internet http://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
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
  unsigned char * ciphertext = (unsigned char *)calloc(1,plaintext_len+AES_BLOCK_SIZE-1);

  /* Encrypt the plaintext */
  *ciphertext_len = encrypt(plaintext, plaintext_len, key, iv,
    ciphertext);
  
  return ciphertext;

}

//Author: taken from internet http://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
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

//Author Caleb Rouleau
unsigned char * decryptAES(unsigned char *ciphertext, int ciphertext_len,
        unsigned char *key, unsigned char *iv, int*plaintext_len) { 
  unsigned char * plaintext = (unsigned char *)calloc(1,ciphertext_len+AES_BLOCK_SIZE);
  *plaintext_len = decrypt(ciphertext, ciphertext_len, key, iv,
    plaintext);
  return plaintext; 
}

//Author Caleb Rouleau
void print(unsigned char *vals, int count) { 
    for(int i = 0; i < count; i++) { 
        printf("%i ",(int)(vals[i]));
    }
    printf("\n"); 
}


/**
 * "Message Authentication Code" i.e. a keyed hash function used for message authentication, which is based on a hash function.
 * Uses OpenSSL's HMAC implementation to produce a...thing
 * Sort of unnecessary since we're just wrapping HMAC, but fewer args this way.
 */

//Author: Mike North with Caleb Rouleau bug fixes
unsigned char * MAC(unsigned char * key, unsigned char * data, int data_len) {
	unsigned char * digest;
	digest = HMAC(EVP_sha1(), key, 20, data, data_len, NULL, NULL);
	//TODO: NOTE: TEST HERE!! It is possible that SHA1 is returning bytes as hex in char, meaning double length (and less random?)
	return digest;
}

unsigned char * getMessageFromLog(struct Li * log, unsigned char *Aj, 
        int *plaintext_len, unsigned char *iv) {
	//get the cipertext
	unsigned char * ciphertext = log->EkDj;
	int ciphertext_len = log->EkDj_len;

	//get the key
	unsigned char key[32];
	for(int i = 0; i<32; i++) { 
		key[i] = '\0';
	}
	struct keySeed *seed = (struct keySeed *)calloc(1, sizeof(struct keySeed));
	seed->W = log->W;
	ustrncpy(seed->A, Aj, 20);
	SHA1((unsigned char *)seed, 20, key);

	printf("ciphertext: ");
	print(ciphertext, ciphertext_len);
	printf("\nciphertext_len: %i\n", ciphertext_len);

	//decrypt the ciphertext
	return decryptAES(ciphertext, ciphertext_len, key, iv, plaintext_len);
}

bool ustrnequ(unsigned char * a, unsigned char *b, int l) { 
    for(int i = 0; i < l; i++) { 
        if(a[i] != b[i]) { 
            return false; 
        }
    }
    return true; 
}
