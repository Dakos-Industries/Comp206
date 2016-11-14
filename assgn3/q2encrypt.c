#include <stdio.h>
#include <string.h>

void main (int argc, char *argv[]){
	FILE *incoming;
	FILE *outgoing;
	//int shift = atoi(argv[4]);
	incoming = fopen(argv[1], "r");
	char recmsg[1000];
	if (fgets(recmsg,1000,incoming) == NULL){
		printf("No message received yet\n");
	}else{
		printf("Received: %s", recmsg);
	}

	fclose(incoming);
	int i = 0;
	while(1){
		char send[1000];
		outgoing = fopen(argv[2],"w");
		fputs("[",outgoing);
		fputs(argv[3],outgoing);
		fputs("] ",outgoing);
		printf("Send:");
		char tmp[1000];
		fgets(tmp,1000,stdin); 
		strcat(send,tmp);
		fputs(send,outgoing);
		fclose(outgoing);
		char newinc[1000];
		while (1){
			incoming = fopen(argv[1],"r");
			if (fgets(newinc, 1000, incoming) == NULL){
			
			}else if (strcmp(newinc,recmsg) == 0){
				fgets(newinc, 1000, incoming);
			}else{
				strcpy(send, "\0");
				strcpy(tmp, "\0");
				strcpy(recmsg,newinc);
				break;
			}		
			fclose(incoming);
		}
		printf("Received: %s", recmsg);
	}
}
