#include "createlog.h"

struct Li createlogDeterministic(unsigned char *ksession, unsigned char *Anot) { 
    struct Li log = emLi; 
    log.W = 0; 
    char message [] = "LogFileInitialization";
    unsigned char *EkDj = encryptAES((unsigned char *)message, strlen(message), 
            ksession, iv, &(log.EkDj_len));
    ustrncpy(log.EkDj, EkDj, log.EkDj_len);
    unsigned char YminusOne [] = {
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0}; 
    struct YhashInput in = emYhashInput;
    for(int i = 0; i < sizeof(struct YhashInput); i++) { 
        ((unsigned char *)&in)[i] = '\0'; 
    }
    ustrncpy(in.YminusOne, YminusOne, 20);
    ustrncpy(in.EkDj, log.EkDj, log.EkDj_len);

    in.W = log.W; 
    SHA1((unsigned char *)&in, sizeof(struct YhashInput), log.Y);
    
    ustrncpy(log.Z, MAC(Anot, log.Y, 20), 20);

    //lognot is created!
    return log;

}

//Author: Caleb Rouleau
void createlog(char *logname) { 
    initOpenSSL();
	logFileName = (char*) calloc(1,strlen(logname));
	strncpy(logFileName, logname, strlen(logname));	
    ustrncpy(originalKey, random256(), 32);
    ustrncpy(Ao, random160(), 20);
    ustrncpy(Aj, Ao, 20);
    logfileNum++;
    struct Li log = createlogDeterministic(originalKey, Ao);


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

