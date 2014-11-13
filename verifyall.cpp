#include "auditlog.h"



void verifyall(char * log-file-name, char * out-file-name) {
	//open the logfile for reading
	FILE * logFile = fopen(log-file-name, "rb");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened. Perhaps it does not exist?\n", log-file-name);
		return;
	}

	//open the outfile for writing
	FILE * outFile = fopen(out-file-name, "wb");
	if (!outFile) {
		printf("The out file named \"%s\" could not be opened.\n", out-file-name);
		return;
	}

	//grab L0 as a starting point for "Lprev". This will require A0 and Ksession
	struct Li Lprev, Lcurr;

	//NOTE: T doesn't know if the logfile has been properly closed, and is not supposed to write
	//anything to file if it has not been closed, So we go through the entire logfile twice,
	//first to find the properly closed message
	bool isClosed = 0;
	for (int twice = 0; twice < 2; twice++) {
		//scan to the start of the file (because we need to read through it twice
		fseek(logFile, 0, SEEK_SET);

		//start with L0 in Lprev
		fread(&Lprev, sizeof(struct Li), 1, logFile);
		if (isClosed) {
				//Write L0's message to the log (if the log is properly closed)
				//char * msg = (char *)getMessageFromLog(&Lprev, Ao);
				//fwrite(msg, strlen(msg), 1, outFile);
				
				//screw it
				fwrite("0 LogfileInitialization\n");
		}
		
		unsigned char Acurr[20];
		ustrncpy(&Acurr, Ao, 20);

		//loop through the log file until all structs have been read, processesing each log entry
		while (fread(&Lcurr, sizeof(struct Li), 1, logFile) != 1) {
			//Compute Acurr
			unsigned char temp[20];
			SHA1(Acurr, 20, temp);
			ustrncpy(Acurr, temp, 20);

			//check that Lcurr.Y = H(Lprev.Y, Lcurr.Ekj(Dj), Lcurr.W)
			unsigned char correctY[20];
			struct YhashInput yInput;
			ustrncpy(yInput.YminusOne, Lprev.Y, 20);
			ustrncpy(yInput.EkDj, Lcurr.EkDj, Lcurr.EkD_len);
			yInput.W = Lcurr.curr;
			SHA1((unsigned char *)yInput, sizeof(struct YhashInput), correctY);
			

			//check that Lcurr.Z = MAC(Acurr, Lcurr.Y)

			
			//if we're here, log is valid so far. if we've also found the file is closed, write to out


			//set Lprev to Lcurr for the next iteration

		}
		//check if the last entry's message is a valid 
	}

	return;
}
