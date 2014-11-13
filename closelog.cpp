//Author: Caleb Rouleau and Mike North
#include "closelog.h"

void closelog() {
	char  message [] = "NormalCloseMessage";	
	time_t t = time(NULL); 
	unsigned char outmessage[strlen(message)+sizeof(time_t)]; 

	ustrncpy(outmessage, (unsigned char *)message, strlen(message));
	ustrncpy(outmessage+strlen(message), (unsigned char *)&t, sizeof(time_t)); 

	add(outmessage, strlen(message)+sizeof(time_t));

	unsigned char clear[] = {
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
        (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)0};
	
	ustrncpy(Aj, clear, 20);
	
	logFileOpen = false;	


}
