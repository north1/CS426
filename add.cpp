#include "auditlog.h"


void add(char* message_string) {

	//Ensure a log is open, print the error and return if not
	//If it is open, store the file pointer in logFile	
	FILE * logFile = fopen(logFileName, "wb");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened.\nPerhaps it does not exist?\n", logFileName);
		return;
	}

	//Read the most recent entry, lastEntry (j-1th in descript)
	//should contain oldType, oldEncryptedMessage, oldHashChain, oldIntegrity
	struct entry * jminus1 = (struct Li *) malloc(sizeof(struct entry)); 
	fseek(logFile, -(sizeof(struct Li)), SEEK_END); //TODO: test this thoroughly for off-by-ones and such?
	fread(jminus1, sizeof(struct entry), 1, logFile);

	//Get the log entry type, Wj --- is this neccessary for us??
	int W = jminus1.W+1;	

	//Form Keyj = H(type+access)
	unsigned char * key = (unsigned char *) malloc(20);
	struct keySeed * seed = (struct keySeed *)malloc(sizeof(struct keySeed));
	keySeed.W = W;
	keySeed.A = Aj;
	SHA1(keySeed, length(access), key);
	
	//Encrypt (with Keyj) the message_string, Dj
	int EkD_len = strlen(message_string) + AES_BLOCK_SIZE;
	unsigned char * EkD = (unsigned char *) malloc(EkD_len);
	EkD = encryptAES(message_string, strlen(message_string), key, iv, &EkD_len);

	//Form Yj = H(oldHashChain, encryptedMessage, type)
	//SHA1(chainContents, strlen(oldEntry.hashChain) + encryptedMessageLength/*+strlen(type)?*/, chainContents);
	unsigned char Y[20];
	struct YhashInput * yInput = (struct YhashInput *)malloc(sizeof(struct YhashInput));
	yInput.YminusOne = jMinus1.Y;
	yInput.EkDj = EkD;
	yInput.W = W;
	SHA1(yInput, sizeof(struct YhashInput), Y);

	//Take Zj = MAC_Aj(hashChain)
	unsigned char Z[20];
	Z = MAC(Aj, Y, 20);
	
	//Update Aj = H(Aj)
	unsigned char Ajplus1[20];
	SHA1(Aj, 20, Ajplus1);
	ustrncpy(Aj, Ajplus1, 20);

	return;
}
