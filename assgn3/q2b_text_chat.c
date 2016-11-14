#include <stdio.h>
#include <string.h>
#include <unistd.h>

void decrypt(int shift, char *argv[]){
	int value = shift;
	//open the file in readable and check if its usable
	FILE *fn;
	fn = fopen(argv[1],"r");
	int c;
	char decryptedWord[1000];
	int i = 0;
	while(!feof(fn)){
		c = fgetc(fn);
		decryptedWord[i] = (char)(c - value);
		i++;
	}
	//close the file
	fclose(fn);
	printf("Received:");
	i--;
	while(i >= 0){
		printf("%c", decryptedWord[i]);
		i--;
	}
	printf("\n");
}
void encrypt(int shift, char *argv[]){

	FILE *fn;
	fn = fopen(argv[2],"r");
	int c;
	char word[1000];
	int i = 0;
	c = fgetc(fn);
	while(c != '\n'){
		word[i] = c + shift;
		c = fgetc(fn);
		++i;
	}
	printf("Fine");	
	fclose(fn);
	fn = fopen(argv[2],"w");
	while(i >= 0){
		fputc(word[i],fn);
		i--;
	}
	fclose(fn);
	printf("STill Fine");
}

void main(int argc, char *argv[]){
	FILE *incoming, *outgoing;
	int shift = atoi(argv[4]);	
	incoming = fopen(argv[1], "r");
	char incommsg[1000];
	int i = 0;
	char tmp[1000];
	while (fscanf(incoming,"%s",tmp) != EOF){
		i++;
		strcat(incommsg,tmp);
		strcat(incommsg," ");

	}
	fclose(incoming);
	if (i == 0){
		printf("Nothing Received Yet\n");
	}else{
		decrypt(shift, argv);
	}	

	while(1){

		outgoing = fopen(argv[2],"w");	
		fputs("[",outgoing);
		fputs(argv[3],outgoing);
		fputs("] ",outgoing);
		printf("Send:");

		char c = getchar();
		while( c != '\n' && c != EOF){
			fputc(c,outgoing);
			c = getchar();
				
		}
		fclose(outgoing);
		encrypt(shift,argv);	
		incoming = fopen (argv[1],"r");
		while(1){
			char compare[1000];
			while (fscanf(incoming, "%s",tmp )!= EOF){
				strcat(compare,tmp);
				strcat(compare," ");
			}
			if (strcmp(compare,incommsg) == 0 || strcmp(compare,"")==0){
				continue;
			}else{
				strcpy(incommsg,compare);
				memset(compare,0,strlen(compare));
				decrypt(shift,argv);
				break;
			}
		}
		fclose(incoming);		
	}
}
