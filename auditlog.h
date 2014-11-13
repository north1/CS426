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
#include "add.h"
#include "closelog.h"
#include "verifyall.h"

//Author: Caleb Rouleau {
extern unsigned char logfileNum;
extern int responseMessageType; 
extern int pnonce; 
extern unsigned char Ao[20];
extern unsigned char Aj[20];
extern char *logFileName;
extern unsigned int logFileNameLen;
extern unsigned char iv[16]; 
extern bool logFileOpen;
extern unsigned char Ko[20];

struct Xi { 
    unsigned char p; 
    time_t d; 
    unsigned char Ao [20];
}; //Xi has length 1+8+20=29

struct Li { 
    int W;
    unsigned char EkDj[500];
    int EkDj_len;
    unsigned char Y[20]; //20 because that's the size of sha1 hash output
    unsigned char Z[20];
};

//used for Yj=H(Yj-1, Ekj(Dj), Wj)
struct YhashInput { 
    unsigned char YminusOne[20]; 
    unsigned char EkDj[500]; 
    unsigned char W; 
};
//} end Author Caleb Rouleau

//Author: Mike North {

//used for Kj = H(Wj, Aj)
struct keySeed {
	int W;
	unsigned char A[20];
};

//int abnormalCloseType = 2; never happens because timeouts can't happen (TA is cool with this)

unsigned char * random128();
unsigned char * random256();
//} end Author Mike North
#endif
