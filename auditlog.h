#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

int logfileNum = 0;
int pnonce = 0; 

struct log { 
    int ksession; //random session key
    int d; //current timestamp
    //int dplus; //timestamp at which U will time out //don't need timeouts
    int id; //unique id for log
    //don't need certificate
    int Ao; //random starting point
};

int logfileInitType = 0; 
int responseMessageType = 1; 
//int abnormalCloseType = 2; never happens because timeouts can't happen (TA is cool with this)

unsigned char * random128();
unsigned char * random256();
