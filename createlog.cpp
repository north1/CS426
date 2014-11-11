#include "auditlog.h"

void initOpenSSL() { 
  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);
}

char * encryptAES(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, int*ciphertext_len) { 
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

//struct __attribute__((__packed__)) Xo { 
struct Xo { 
    unsigned char p; 
    time_t d; 
    unsigned char [20] Ao;
}

void createlog(char *logname) { 
    initOpenSSL();
    struct log * log = (struct log *)malloc(sizeof(struct log));
    int ksession = rand(); 
    time_t d = time(NULL); 
    unsigned char id = logfileNum; 
    logfileNum++; 
    log->Ao = rand(); 
    unsigned char * Xo = (int *)malloc(sizeof(unsigned char));
    //Xo is p,d,Ao
    Xo[0] = p; 
    addToArray(Xo+1, d); 

    Xo[1] = log->d; 
    Xo[2] = log->Ao;
    //Xo[0] = don't need Xo because it is involved 
    //in signing stuff
    int p = pnonce;

    int Mo_len;
    unsigned char *Mo = encryptAES(//encrypt Xo with ksession
        
    
        
    tCreatelog(p, id, Xo); 

    int Wo = LogfileInitType; 
    EkjDj = encrypt (d,dplus,id,

}

void tCreatelog(int p, int id, int *Xo) { 
    //todo t's stuff in createlog
}
