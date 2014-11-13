#include "createlog.h"

//Author: Caleb Rouleau
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
    ustrncpy(Ao, random160(), 20);
    ustrncpy(Aj, Ao, 20);

    struct Li log; 
    log.W = logfileInitType; 
    char message [] = "LogFileInitialization";
    unsigned char *EkDj = encryptAES((unsigned char *)message, strlen(message), 
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
    
    ustrncpy(log.Z, MAC(Ao, log.Y, 20), 20);

    //logo is create!

    FILE *file_ptr = fopen(logname,"wb");
	if (!file_ptr) {
		printf("The log named \"%s\" could not be opened.\n", logFileName);
		return;
	}	
    fwrite(&log, sizeof(struct Li), 1, file_ptr);
    fclose(file_ptr);
	logFileOpen = true;

    char ms[] = "LogfileOpenSuccess";
    add((unsigned char *)ms, strlen(ms));
}

