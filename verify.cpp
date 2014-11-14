#include "verify.h"

//Author: Caleb Rouleau
bool verifyFirstLog(FILE *logFile, bool shouldPrint) { 
    //because the first log is created deterministically and we have all the values, 
    //we can simply compare the two logs
    unsigned char AoNew[20]; 
    ustrncpy(AoNew, Ao, 20); 
    unsigned char newKey[32];
    ustrncpy(newKey, originalKey, 32);
   
    struct Li correctLog = createlogDeterministic(originalKey, AoNew);
    struct Li actualLog = emLi;
    int fread_ret = fread(&actualLog, sizeof(struct Li), 1, logFile);
    bool success;
    if(fread_ret == 1 
            && ustrnequ((unsigned char *)&correctLog, (unsigned char *)&actualLog, sizeof(struct Li))) { 
        if(shouldPrint) {
            printf("LogFileInitialization\n");
        }
        success = true; 
    } else { 
        if(shouldPrint) {
            printf("Failed verification\n");
        }
        success = false;
    }
    fseek(logFile, 0, SEEK_SET);
    return success;
}

//Written by Caleb Rouleau using code from Mike North
void verify(int entry_no) {
    if(!logFileOpen) { 
        printf("cannot verify a single log from a closed log file! (must use verifyall)\n");
    }
	//open the logfile for reading
	FILE * logFile = fopen(logFileName, "rb");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened. Perhaps it does not exist?\n", logFileName);
		return;
	}

    if(entry_no == 0) { 
        verifyFirstLog(logFile, true); 
        fclose(logFile);
        return;
    }
    //grab L0 as a starting point for "Lprev". This will require A0 and Ksession
    struct Li Lprev = emLi; 
    struct Li Lcurr = emLi;

    fseek(logFile, 0, SEEK_SET);

    //start with L0 in Lprev
    fread(&Lprev, sizeof(struct Li), 1, logFile);

    unsigned char Acurr[20];
    ustrncpy(Acurr, Ao, 20);

    unsigned char Aprev[20];

    bool failed = true;

    //loop through the log file until all structs have been read, processesing each log entry
    for(int i = 1; i <= entry_no; i++) { 
        printf("in for\n");
        int fread_ret = fread(&Lcurr, sizeof(struct Li), 1, logFile);
        if(fread_ret != 1) { 
            printf("breaking because couldn't read more\n");
            break; 
        }
        printf("Lcurr.W: %i\n", Lcurr.W);
        fflush(stdout);

        if(i == entry_no) { 
            //check that Lcurr.Y = H(Lprev.Y, Lcurr.Ekj(Dj), Lcurr.W)
            unsigned char correctY[20];
            struct YhashInput yInput = emYhashInput;
            for(int i = 0; i < sizeof(struct YhashInput); i++) { 
                ((unsigned char *)&yInput)[i] = '\0';
            }

            ustrncpy(yInput.YminusOne, Lprev.Y, 20);
            ustrncpy(yInput.EkDj, Lcurr.EkDj, Lcurr.EkDj_len);
            yInput.W = Lcurr.W;
            SHA1((unsigned char *)&yInput, sizeof(struct YhashInput), correctY);
            if (!ustrnequ(Lcurr.Y, correctY, 20)) {
                printf("Failed verification: Y is not correct.\n");
                fflush(stdout);
                return;
            }

            //check that Lcurr.Z = MAC(Acurr, Lcurr.Y)
            unsigned char correctZ[20];
            ustrncpy(correctZ, MAC(Acurr, Lcurr.Y, 20), 20);
            if (!ustrnequ(Lcurr.Z, correctZ, 20)) {
                printf("Failed verification: Z is not correct.\n");
                fflush(stdout);
                return;
            }

            //if we're here, log is valid so far. if we've also found the file is closed, write to out
            int plaintext_len;
            char * message = (char *)getMessageFromLog(&Lcurr, Acurr, &plaintext_len, iv);
            for (int i = 0; i < plaintext_len; i++) {
                fputc(message[i], stdout);
            }
            fputc('\n', stdout);
            return;
        }

        //set Lprev to Lcurr for the next iteration
        ustrncpy((unsigned char *)&Lprev, (unsigned char *)&Lcurr, sizeof(struct Li));

        //Compute Acurr
        unsigned char temp[20];
        SHA1(Acurr, 20, temp);
        ustrncpy(Aprev, Acurr, 20);
        ustrncpy(Acurr, temp, 20);
    }

    if(failed) { 
        printf("Failed verification\n");
    }

    fclose(logFile);
	return;
}
