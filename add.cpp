#include "auditlog.h"

//Author: Pair programming Mike North, Caleb Rouleau
void add(unsigned char* message_string, int len) {

	if (!logFileOpen) {
		printf("A log file has not yet been opened. Use createlog [logfilename].log]\n");
		return;
	}

	//Ensure a log is open, print the error and return if not
	//If it is open, store the file pointer in logFile	
	FILE * logFile = fopen(logFileName, "rb");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened.\n", logFileName);
		return;
	}

	//Read the most recent entry, lastEntry (j-1th in descript)
	//should contain oldType, oldEncryptedMessage, oldHashChain, oldIntegrity
	struct Li * jminus1 = (struct Li *) malloc(sizeof(struct Li)); 
	fseek(logFile, -(sizeof(struct Li)), SEEK_END);
	fread(jminus1, sizeof(struct Li), 1, logFile);
	fclose(logFile);

	//print((unsigned char *)jminus1, sizeof(struct Li));
	
	//Get the log entry type, Wj --- is this neccessary for us??
	int W = jminus1->W+1;	

	//Form Keyj = H(type+access)
	unsigned char * key = (unsigned char *) malloc(20);
	struct keySeed * seed = (struct keySeed *)malloc(sizeof(struct keySeed));
	seed->W = W;
	ustrncpy(seed->A, Aj, 20);
	SHA1((unsigned char *)seed, 20, key);
	
	//Encrypt (with Keyj) the message_string, Dj
	int EkD_len = len + AES_BLOCK_SIZE;
	unsigned char * EkD = (unsigned char *) malloc(EkD_len);
	EkD = encryptAES(message_string, len, key, iv, &EkD_len);

	//Form Yj = H(oldHashChain, encryptedMessage, type)
	unsigned char Y[20];
	struct YhashInput * yInput = (struct YhashInput *)malloc(sizeof(struct YhashInput));
	ustrncpy(yInput->YminusOne, jminus1->Y, 20);
	ustrncpy(yInput->EkDj, EkD, EkD_len);
	yInput->W = W;
	SHA1((unsigned char *)yInput, sizeof(struct YhashInput), Y);

	//Take Zj = MAC_Aj(hashChain)
	unsigned char Z[20];
	ustrncpy(Z, MAC(Aj, Y, 20), 20);
	
	//Update Aj = H(Aj)
	unsigned char Ajplus1[20];
	SHA1(Aj, 20, Ajplus1);
	ustrncpy(Aj, Ajplus1, 20);


	//all together now!
	struct Li log;
	log.W = W;
	ustrncpy(log.EkDj, EkD, EkD_len);
	log.EkDj_len = EkD_len;
	ustrncpy(log.Y, Y, 20);
	ustrncpy(log.Z, Z, 20);

	//write the new log to file
	logFile = fopen(logFileName, "ab");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened.\n", logFileName);
		return;
	}
//	fseek(logFile, 0, SEEK_END);
    fwrite(&log, sizeof(struct Li), 1, logFile);
    fclose(logFile);

	return;
}
