#include "verifyall.h"

void verifyall(char * log_file_name, char * out_file_name) {
	//open the logfile for reading
	FILE * logFile = fopen(log_file_name, "rb");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened. Perhaps it does not exist?\n", log_file_name);
		return;
	}
    
	//open the outfile for writing
	FILE * outFile = fopen(out_file_name, "wb");
	if (!outFile) {
		printf("The out file named \"%s\" could not be opened.\n", out_file_name);
		return;
	}
    if(verifyFirstLog(logFile, false)) {
        char initMsg[] = "LogfileInitialization\n"; 
        fwrite(initMsg, strlen(initMsg),1, outFile);
    } else { 
	    printf("Failed verification\n");
        return;
    }

	//grab L0 as a starting point for "Lprev". This will require A0 and Ksession
	struct Li Lprev = emLi; 
	struct Li Lcurr = emLi;

	//NOTE: T doesn't know if the logfile has been properly closed, and is not supposed to write
	//anything to file if it has not been closed, So we go through the entire logfile twice,
	//first to find the properly closed message
	bool isClosed = false;
	for (int twice = 0; twice < 2; twice++) {
		//scan to the start of the file (because we need to read through it twice
		fseek(logFile, 0, SEEK_SET);

		//start with L0 in Lprev
		fread(&Lprev, sizeof(struct Li), 1, logFile);
		
		unsigned char Acurr[20];
		ustrncpy(Acurr, Ao, 20);

		unsigned char Aprev[20];

		//loop through the log file until all structs have been read, processesing each log entry
		while (fread(&Lcurr, sizeof(struct Li), 1, logFile) == 1) {
            printf("Lcurr.W: %i\n", Lcurr.W);
            fflush(stdout);

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
			if (isClosed) {
				int plaintext_len;
				char * message = (char *)getMessageFromLog(&Lcurr, Acurr, &plaintext_len, iv);
				for (int i = 0; i < plaintext_len; i++) {
					fputc(message[i], outFile);
				}
				fputc('\n', outFile);
			}

			//set Lprev to Lcurr for the next iteration
			ustrncpy((unsigned char *)&Lprev, (unsigned char *)&Lcurr, sizeof(struct Li));

			//Compute Acurr
			unsigned char temp[20];
			SHA1(Acurr, 20, temp);
			ustrncpy(Aprev, Acurr, 20);
			ustrncpy(Acurr, temp, 20);
		}
		//check if the last entry's message is a valid closelog
		int plaintext_len;
		char *message = (char *)getMessageFromLog(&Lprev, Aprev, &plaintext_len, iv);
		printf("Message: ");
		print((unsigned char *) message, strlen(message));
		printf("\"NormalCloseMessage\": ");
		print((unsigned char *) "NormalCloseMessage", strlen("NormalCloseMessage"));
		if (strncmp(message, "NormalCloseMessage", strlen("NormalCloseMessage")) == 0) {
			printf("Setting isClosed to true\n");
			isClosed = true;
		} else { 
            printf("Failed verification: incorrect close message\n");
            return;
        }
	}
    fclose(logFile);
    fclose(outFile);
	return;
}
