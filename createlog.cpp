#include "createlog.h"

void tCreatelog(struct Mi Mo, unsigned char * iv) { 
    //returns M1 = p, K1
    int Xo_len; 
    struct Xi *Xo = (struct Xi *)decryptAES(Mo.EkXi, Mo.EkXi_len, Mo.ksession, iv, &Xo_len);
    printf("T: ksession is:\n");
    print(Mo.ksession, 32);
    printf("T: time of log is %i\n", (int)(Xo->d));
    //returns X1 = p, IDlog,hash(Xo)
    
    //X1 = p,IDlog,hash(Xo) 
    struct Xi X1; 
    X1.p = Xo->p; 
    //X1.d = 

    
}

void createlog(char *logname) { 
    initOpenSSL();

	logFileName = (char*) malloc(strlen(logname));
	strncpy(logFileName, logname, strlen(logname));	

    unsigned char * ksession = random256(); 
    printf("U: ksession is:\n");
    print(ksession, 32);
    time_t d = time(NULL); 
    unsigned char id = ++logfileNum; 
    printf("U: time of log is %i\n", (int)d);
    unsigned char *Ao = random160();
    struct Xi xo;
    xo.p = pnonce; 
    xo.d = d; 
    ustrncpy(xo.Ao, Ao, 20);

    int p = pnonce;

    int EkXi_len;
    unsigned char *EkXi = encryptAES((unsigned char *)&xo, (int)sizeof(struct Xi),
            ksession, iv, &EkXi_len); 
  
    struct Mi Mo; 
    Mo.p = p; 
    ustrncpy(Mo.ksession, ksession, 32);
    ustrncpy(Mo.EkXi, EkXi, EkXi_len);
    Mo.EkXi_len = EkXi_len; 

    tCreatelog(Mo, iv); 

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

	//print((unsigned char *)&log, sizeof(struct Li));
    FILE *file_ptr = fopen(logname,"wb");
	if (!file_ptr) {
		printf("The log named \"%s\" could not be opened.\n", logFileName);
		return;
	}	
    fwrite(&log, sizeof(struct Li), 1, file_ptr);
    fclose(file_ptr);
	logFileOpen = true;
}
/*
void createlog2(char *logname) {
	//store the logFileName in a global
	logFileName = (char*) malloc(strlen(logname));
	strncpy(logFileName, logname, strlen(logname));	

	//form the first log entry
	struct Li * firstLog = 
}
*/

