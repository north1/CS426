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

unsigned char logfileNum = 0;
int pnonce = 0; 

struct Xi { 
    unsigned char p; 
    time_t d; 
    unsigned char Ao [20];
};

struct Mi { 
    unsigned char p; 
    unsigned char ksession [256]; 
    unsigned char *EkMo; 
    int EkMo_len;
};

struct Li { 
    int W;
    unsigned char * EkD;
    int EkD_len;
    unsigned char *Y; 
    int Y_len;
    //removed Z because unneeded
};

struct Dj { 
    time_t d; 
    unsigned char id; 
    struct Mi Mi;
};

struct YhashInput { 
    unsigned char * YminusOne; 
    unsigned char * EkD; 
    unsigned char * W; 
};

struct entry {
	int W; //entry type, possibly unnecessary, subject to change
	unsigned char * EkD; //arbitrary size, may change?
	int EkD_len;
	unsigned char * Y; //note: initial entry should have hashChain of all zeros
	int Y_len;
	unsigned char * Z; //= MAC_Aj(hashChain) -- definitely subject to change since I have no goddamn idea what MAC is
};

int logfileInitType = 0; 
int responseMessageType = 1; 
//int abnormalCloseType = 2; never happens because timeouts can't happen (TA is cool with this)

unsigned char * random128();
unsigned char * random256();
#endif
