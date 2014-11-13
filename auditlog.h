#ifndef AUDIT_LOG_INCLUDED
#define AUDIT_LOG_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include "utilities.h"
#include "createlog.h"

extern unsigned char logfileNum;
extern int logfileInitType; 
extern int responseMessageType; 
extern int pnonce; 
extern unsigned char Ao[20];
extern unsigned char Aj[20];
extern unsigned char *logFileName;
extern unsigned int logFileNameLen;
extern unsigned char iv[16]; 

struct Xi { 
    unsigned char p; 
    time_t d; 
    unsigned char Ao [20];
}; //Xi has length 1+8+20=29

struct Mi { 
    unsigned char p; 
    unsigned char ksession [32]; 
    unsigned char EkXi[sizeof(struct Xi)+AES_BLOCK_SIZE];
    int EkXi_len;
};

struct Dj { 
    time_t d; 
    unsigned char id; 
    struct Mi Mi;
};

struct Li { 
    int W;
    unsigned char EkDj[sizeof(Dj)+AES_BLOCK_SIZE];
    int EkDj_len;
    unsigned char Y[20]; //20 because that's the size of sha1 hash output
    unsigned char Z[20];
};

//used for Yj=H(Yj-1, Ekj(Dj), Wj)
struct YhashInput { 
    unsigned char YminusOne[20]; 
    unsigned char EkDj[sizeof(Dj)+AES_BLOCK_SIZE]; 
    unsigned char W; 
};

//used for Kj = H(Wj, Aj)
struct keySeed {
	int W;
	unsigned char A[20];
};

//int abnormalCloseType = 2; never happens because timeouts can't happen (TA is cool with this)

unsigned char * random128();
unsigned char * random256();
#endif
