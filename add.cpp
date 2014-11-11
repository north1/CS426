#include "auditlog.h"

void add(char* message_string) {

	//Ensure a log is open, print the error and return if not
	//If it is open, store the file pointer in logFile	
	char * logFileName; //TODO: set this from...whereever we're storing it?
	FILE * logFile = fopen(logFileName, "wb");
	if (!logFile) {
		printf("The log named \"%s\" could not be opened.\nPerhaps it does not exist?\n", logFileName);
		return;
	}

	//Read the most recent entry, lastEntry (j-1th in descript)
	//should contain oldType, oldEncryptedMessage, oldHashChain, oldIntegrity
	//call it oldEntry
	struct entry * oldEntry = (struct entry *) malloc(sizeof(struct entry)); 
	fseek(logFile, -(sizeof(struct entry)), SEEK_END); //TODO: test this thoroughly for off-by-ones and such?
	fread(oldEntry, sizeof(struct entry), 1, logFile);

	//Get the access code, Aj
	//call this access
	unsigned char access[20]; //TODO: assign this to...wherever the hell it's stored?

	//Get the log entry type, Wj --- is this neccessary for us??
	//call this type
	//TODO: seriously do we need this?
	
	//Form Keyj = H(type+access)
	//call this key
	unsigned char * key = (unsigned char *) malloc(20);
	//unsigned char keySeed[40] = strcat(type, access); //TODO: if we're using type, uncomment this and replace access with keySeed in next line
	SHA1(access, length(access), key);
	
	//Encrypt (with Keyj) the message_string, Dj
	//call this encryptedMessage
	
	
	//Form Yj = H(oldHashChain, encryptedMessage, type)
	//call this hashChain
	
	//Take Zj = MAC_Aj(hashChain)
	//call this integrity
	
	//Update Aj = H(Aj) (pretty sure we're only supposed to keep one at a time globally, except "T" (Server) needs access to A0)
	
	return;
}
