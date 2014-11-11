#include "auditlog.h"

void createlog(char *logname) { 
    initOpenSSL();
    struct log * log = (struct log *)malloc(sizeof(struct log));
    unsigned char * ksession = random256(); 
    unsigned char * iv = random128();
    time_t d = time(NULL); 
    unsigned char id = logfileNum; 
    unsigned char *Ao = random160();
    logfileNum++; 
    struct Xi xo;
    xo.p = p; 
    xo.d = d; 
    strncpy(xo.Ao, Ao, 20);

    int p = pnonce;

    int EkMo_len;
    unsigned char *EkMo = encryptAES((unsigned char *)&xo, sizeof(struct Xi),
            ksession, iv, &EkMo_len); 

    struct Mi Mo; 
    Mo.p = p; 
    Mo.ksession = ksession; 
    Mo.EkMo = EkMo; 
    Mo.EkMo_len = EkMo_len; 

    tCreatelog(Mo); 

    struct Li log; 
    log.W = logfileInitType; 
    struct Dj D; 
    D.d = d; 
    D.id = id; 
    D.Mi = Mo; 
    log.EkD = encryptAES((unsigned char *)&D, sizeof(struct Dj), 
            ksession, iv, &(log.EkD_len));
    unsigned char YminusOne [] = {
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0}; 
    struct YhashInput in;
    in.YminusOne = YminusOne; 
    in.EkD = log.EkD; 
    in
    log.Y = hash(W

}

void tCreatelog(struct Mi Mo) { 
    //todo t's stuff in createlog
}
