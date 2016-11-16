#include <stdio.h>
#include <string.h>

void main (int argc, char *argv[]){
	//File set up and error checks: argument number and null files
	FILE *incoming;
	FILE *outgoing;
	if (argc < 4){
		printf("Error");
		return;
	}
	incoming = fopen(argv[1], "r");
	if (incoming == NULL){
		printf("ERROR");
		return;
	}
	char recmsg[1000];
	//CHeck to see if file has contents
	if (fgets(recmsg,1000,incoming) == NULL){
		printf("No message received yet\n");
	}else{
		printf("Received: %s\n", recmsg);
	}
	fclose(incoming);
	int i = 0;
	
	while(1){
		//Puts user info into send array
		char send[1000];
		outgoing = fopen(argv[2],"w");
		char termSeq[100];
		fputs("[",outgoing);
		fputs(argv[3],outgoing);
		fputs("] ",outgoing);
		char tmp[1000];
		printf("Send:");
		//gets user input and puts it into the tmp array
		fgets(tmp,1000,stdin);
		//Fuse the tmp array and the send array to create the message to send
		strcat(send,tmp);
		fputs(send,outgoing);
		fclose(outgoing);
		char newinc[1000];
		// Now we wait for the other person to respond
		while (1){
			//sleep was added to deal with reading the file wrong
			sleep(2);
			incoming = fopen(argv[1],"r");
			//checks to see if anything was written and if it was different than before
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
