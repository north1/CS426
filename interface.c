#include <stdio.h>
#include <stdlib.h>

void main() {
	size_t bufSize = 100*sizeof(char);
	char *inputLine;
	inputLine = (char*)malloc(bufSize); //arbitrary size

	while (1) {
		printf(	"Enter one of the following commands:\n"
			"createlog [filename].log\n"
			"add [message_string]\n"
			"closelog\n"
			"verify [entry_no]\n"
			"verifyall [log-file-name].log [out-file-name].txt\n"
			"[Use ctrl+c to terminate program]\n\n");
	
		//fgets(inputLine, sizeof(inputLine), stdin);
		getline(&inputLine, &bufSize, stdin);

		printf("\nYou entered: %s\n", inputLine);
	}
	return;

}
