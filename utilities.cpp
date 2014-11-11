#include "auditlog.h"

unsigned char * random128() {
	unsigned char * ret = (unsigned char*) malloc(16); //16 bytes = 128 bits
	for (int i = 0; i < 16; i++) {
		ret[i] = (unsigned char)(rand()%256);	
	}
	return ret;
}


unsigned char * random256() {
	unsigned char * ret = (unsigned char *) malloc(32); //32 bytes = 256 bits
	for (int i = 0; i < 32; i++) {
		ret[i] = (unsigned char)(rand()%256);
	}
	return ret;
}
