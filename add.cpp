#include "auditlog.h"

void add(char* message_string) {
	
	//Read the most recent entry, lastEntry (j-1th in descript)
	//should contain oldType, oldEncryptedMessage, oldHashChain, oldIntegrity
	//
	//Get the access code, Aj
	//call this access
	//
	//Get the log entry type, Wj --- is this neccessary for us??
	//call this type
	//
	//Form Keyj = H(Wj, Aj)
	//call this key
	//
	//Encrypt (with Keyj) the message_string, Dj
	//call this encryptedMessage
	//
	//Form Yj = H(oldHashChain, encryptedMessage, type)
	//call this hashChain
	//
	//Take Zj = MAC_Aj(hashChain)
	//call this integrity
	//
	//Update Aj = H(Aj) (pretty sure we're only supposed to keep one at a time globally, except "T" (Server) needs access to A0)
	
	return;
}
