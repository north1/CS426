#include "auditlog.h"


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
