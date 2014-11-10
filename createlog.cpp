#include "auditlog.h"


void createlog(char *logname) { 
    struct log * log = (struct log *)malloc(sizeof(struct log));
    log->ksession = rand(); 
    log->d = time(NULL); 
    log->id = logfileNum; 
    logfileNum++; 
    log->Ao = rand(); 
    int * Xo = (int *)malloc(sizeof(int)*4);
    Xo[0] = log->p; 
    Xo[1] = log->d; 
    Xo[2] = log->Ao;
    //Xo[0] = don't need Xo because it is involved 
    //in signing stuff
    int p = pnonce;
    Mo = encrypt Xo with ksession
    tCreatelog(p, id, Xo); 

    int Wo = LogfileInitType; 
    EkjDj = encrypt (d,dplus,id,

}

void tCreatelog(int p, int id, int *Xo) { 
    //todo t's stuff in createlog
}
