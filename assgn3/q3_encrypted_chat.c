#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Same as in Q1A
void decrypt(int shift, char *argv[]){
	int value = shift;
	FILE *fn;
	fn = fopen(argv[1],"r");
	int c;
	char decryptedWord[1000];
	int i = 0;
	//Goes through characters untill the end
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
//Encryption algorithm based on reverse ceasar algorithm
//Takes in the shift amount and applies it to every char
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
	//Basically does the same thing as Question 2 but
	//Adds the use of functions to encrypt and decrypt 
	// when sending and receiving. Otherwise it is 
	//exactly the same code
	FILE *incoming;
	FILE *outgoing;
	if (argc < 5){
		printf("Not enought arguments");
		exit(0);
	}
	int shift = atoi(argv[4]);
	if (shift == 0){
		printf("ERROR: specifiy a shift greater than 0");
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
		decrypt(shift, argv);//print out decrypted string
	}

	fclose(incoming);
	int i = 0;
	while(1){
		char send[1000];
		outgoing = fopen(argv[2],"w");
		fputs("[",outgoing);
		fputs(argv[3],outgoing);
		fputs("] ",outgoing);
		printf("Send:     ");
		char tmp[1000];
		fgets(tmp,1000,stdin);
		if (tmp[0]== '\0'){
			printf("\nSession ended due to end of input stream\n");
			exit(0);
		} 
		strcat(send,tmp);
		fputs(send,outgoing);
		fclose(outgoing);
		encrypt(shift,argv);//encrypt the message 
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
