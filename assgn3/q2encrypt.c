#include <stdio.h>
#include <string.h>

void decrypt(int shift, char *argv[]){
	int value = shift;
	FILE *fn;
	fn = fopen(argv[1],"r");
	int c;
	char decryptedWord[1000];
	int i = 0;
	while(!feof(fn)){
		c = fgetc(fn);
		if(c == 0){
			break;
		}
		decryptedWord[i] = (char)(c - value);
		i++;
	}
	//close the file
	fclose(fn);
	--i;
	printf("Received: ");
	while(i >= 0){
		printf("%c", decryptedWord[i]);
		i--;
	}
}
void encrypt(int shift, char *argv[]){

	FILE *fn;
	fn = fopen(argv[2],"r");
	char word[1000];
	fgets(word, 1000, fn);
	fclose(fn);
	fn = fopen(argv[2],"w");
	int i = strlen(word);
	i--;;
	while(i >= 0){
		fputc((char)(word[i]+shift), fn);
		i--;
	}
	fputc('\0',fn);
	fclose(fn);
}
void main (int argc, char *argv[]){
	FILE *incoming;
	FILE *outgoing;
	int shift = atoi(argv[4]);
	if (shift == 0){
		printf("ERROR");
		return;
	}
	incoming = fopen(argv[1], "r");
	if (incoming == NULL){
		printf("ERROR");
		return;
	}
	char recmsg[1000];
	if (fgets(recmsg,1000,incoming) == NULL){
		printf("No message received yet\n");
	}else{
		decrypt(shift, argv);
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
		encrypt(shift,argv);
		char newinc[1000];
		while (1){
			sleep(2);
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
		decrypt(shift,argv);
	}
}
