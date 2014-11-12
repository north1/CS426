#include "createlog.h"

void tCreatelog(struct Mi Mo) { 
    //todo t's stuff in createlog
}

void createlog(char *logname) { 
    initOpenSSL();
    unsigned char * ksession = random256(); 
    unsigned char * iv = random128();
    time_t d = time(NULL); 
    unsigned char id = logfileNum; 
    unsigned char *Ao = random160();
    logfileNum++; 
    struct Xi xo;
    xo.p = pnonce; 
    xo.d = d; 
    ustrncpy(xo.Ao, Ao, 20);

    int p = pnonce;

    int EkXi_len;
    unsigned char *EkXi = encryptAES((unsigned char *)&xo, sizeof(struct Xi),
            ksession, iv, &EkXi_len); 

    struct Mi Mo; 
    Mo.p = p; 
    ustrncpy(Mo.ksession, ksession, 32);
    ustrncpy(Mo.EkXi, EkXi, EkXi_len);
    Mo.EkXi_len = EkXi_len; 

    tCreatelog(Mo); 

    struct Li log; 
    log.W = logfileInitType; 
    struct Dj D; 
    D.d = d; 
    D.id = id; 
    D.Mi = Mo; 
    unsigned char *EkDj = encryptAES((unsigned char *)&D, sizeof(struct Dj), 
            ksession, iv, &(log.EkDj_len));
    ustrncpy(log.EkDj, EkDj, log.EkDj_len);
    unsigned char YminusOne [] = {
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0}; 
    struct YhashInput in;
    for(int i = 0; i < sizeof(struct YhashInput); i++) { 
        ((unsigned char *)&in)[i] = '\0'; 
    }
    ustrncpy(in.YminusOne, YminusOne, 20);
    ustrncpy(in.EkDj, log.EkDj, log.EkDj_len);
    in.W = log.W; 
    SHA1((unsigned char *)&in, sizeof(struct YhashInput), log.Y);

    FILE *file_ptr = fopen(logname,"wb");
    fwrite(&log, sizeof(struct Li), 1, file_ptr);
    fclose(file_ptr);
}

