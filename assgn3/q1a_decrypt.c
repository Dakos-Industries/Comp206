#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[]){
	if (argc < 3){
		printf("Error: Not enough arguments");
		return;
	}
	//Get the shift from the terminal
	int value = atoi(argv[1]);
	if (value == 0){
		printf("Error");
		return;
	}
	//open the file in readable and check if its usable
	FILE *fn;
	fn = fopen(argv[2],"r");
	if (fn == NULL){
		printf("Error");
		return;
	}
	int c;
	char decryptedWord[1000];
	int i = 0;
	//Simply looks at every character in the fila and shifts it by the 
	//specified shift
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
	while(i >= 0){
		printf("%c", decryptedWord[i]);
		i--;
	}
	printf("\n");
}
