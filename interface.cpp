//Author mostly Mike North and some Caleb Rouleau bug fixes
#include "auditlog.h"

unsigned char logfileNum;
int pnonce; 
int responseMessageType;
unsigned char Ao[20]; 
unsigned char Aj[20];
char * logFileName;
unsigned int logFileNameLen;
unsigned char iv [16];
bool logFileOpen;
unsigned char Ko[20];

struct Xi emXi;
struct Li emLi;
struct YhashInput emYhashInput;
struct keySeed emkeySeed;

int main() {
	struct Xi *ex = (struct Xi*)calloc(1,sizeof(struct Xi));
	emXi = *ex;
	struct Li *el = (struct Li*)calloc(1,sizeof(struct Li));
	emLi = *el;
	struct YhashInput *ey = (struct YhashInput*)calloc(1,sizeof(struct YhashInput));
	emYhashInput = *ey;
	struct keySeed *es = (struct keySeed*)calloc(1,sizeof(struct keySeed));
	emkeySeed = *es;

    ustrncpy(iv, random128(), 16); 
    logfileNum = 1; 
    pnonce = 1; 
    responseMessageType = 1;
	logFileOpen = false;
    
	size_t bufSize = 100*sizeof(char);
	char *inputLine, *cmd, *arg, *arg2;
	inputLine = (char*)malloc(bufSize); //arbitrary size

	srand(time(NULL));

	while (1) {
		/*printf(	"Enter one of the following commands:\n"
			"createlog [filename].log\n"
			"add [message_string]\n"
			"closelog\n"
			"verify [entry_no]\n"
			"verifyall [log-file-name].log [out-file-name].txt\n"
			"[Use ctrl+c to terminate program]\n\n");
		fflush(stdout);
*/
		getline(&inputLine, &bufSize, stdin); //Get the full input text
		cmd = strtok(inputLine, " \n"); //Get the first word (should be the command))

		if (strcmp(cmd, "createlog") == 0) {
			arg = strtok(NULL, " \n");
			printf("Command: createlog\n");
			printf("Argument: %s\n", arg);
		    createlog(arg); 
            pnonce++;
		}

		else if (strcmp(cmd, "add") == 0) {
			arg = strtok(NULL, " \n");
			printf("Command: add\n");
			printf("Argument: %s\n", arg);
            int msgLen = strlen(arg); 
            if(msgLen > 450) { 
                arg[450] = '\0'; 
            }
			add((unsigned char *) arg, strlen(arg));
		}


		else if (strcmp(cmd, "closelog") == 0) {
			printf("Command: closelog\n");
			closelog();
		}

		else if (strcmp(cmd, "verify") == 0) {
			arg = strtok(NULL, " \n");
			printf("Command: verify\n");
			printf("Argument: %s\n", arg);

		}

		else if (strcmp(cmd, "verifyall") == 0) {
			arg = strtok(NULL, " \n");
			arg2 = strtok(NULL, " \n");
			printf("Command: verifyall\n");
			printf("Argument 1: %s\n", arg);
			printf("Argument 2: %s\n", arg2);
            verifyall(arg, arg2);
		}

		else {
			printf("Invalid command\n\n");
		}
	}

	return 0;
}
