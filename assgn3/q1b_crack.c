#include <stdio.h>
#include <string.h>

//Funtion that takes in the encrypted string, its length, and the shift
int decrypt(char *encrypt, int index, int shift){
	int aCount = 0;
	int zCount = 0;
	int tmpIndex = index;
	//Shifts the characters while keeping count of the amount of 'a's and 'z's
	while(tmpIndex >= 0){
		if ( (char)(encrypt[tmpIndex]-shift) == 'a' || (char)(encrypt[tmpIndex]- shift) == 'A'){
			aCount++;
		}
		if ((char)(encrypt[tmpIndex]-shift) == 'z' || (char)(encrypt[tmpIndex] - shift) == 'Z'){
			zCount++;
		}
		tmpIndex--;
	}
	//if we have an a and a z then print out the decrypted string
	//else return 0 for false
	if (aCount > 0 && zCount > 0){
		printf("%d\n",shift);
		while(index >= 0){
			printf("%c", encrypt[index] -shift);
			index--;
		}	
		printf("\n");
		return 1;
	}else {
		return 0;
	}
}

void main(int argc, char *argv[]){
	if (argc < 2){
		printf("Error: Not enough arguments");
		return;
	}
	//open the file in readable and check if its usable
	FILE *fn;
	fn = fopen(argv[1],"r");
	if (fn == NULL){
		printf("Error");
		return;
	}
	int c;
	char decryptedWord[1000];
	int Index = 0;
	//saving the encrypted string to a char array
	while(!feof(fn)){
		c = fgetc(fn);
		if(c == 0){
			break;
		}
		decryptedWord[Index] = (char)(c);
		Index++;
	}
	//close the file
	fclose(fn);
	//decrement the index to avoid extra characters
	--Index;
	int shift = 0;
	//run untill decripted
	while(decrypt(decryptedWord,Index,shift) != 1){
		++shift;
	}
}
