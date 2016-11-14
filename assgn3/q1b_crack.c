#include <stdio.h>
#include <string.h>

int decrypt(char *encrypt, int index,int start, int caps){
	int aCount = 0;
	int zCount = 0;
	int shift = 0;
	if (caps == 1){
		shift = 191 + (int) (encrypt[start]);
	}else{
		shift = 159 + (int) (encrypt[start]); 
	}
	while(start >= 0){
		if ( (char)(encrypt[start]-shift) == 'a' || (char)(encrypt[start]- shift) == 'A'){
			aCount++;
		}
		if ((char)(encrypt[start]-shift) == 'z' || (char)(encrypt[start] - shift) == 'Z'){
			zCount++;
		}
		start--;
	}
	if (aCount > 0 && zCount > 0){
		printf("%d\n",shift);
		while(index >= 0){
		printf("%c", encrypt[index] -shift);
		index--;
	}
	printf("\n");
	return 1;

	}else {return 0;}
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
	int lastIndex = 0;
	while(!feof(fn)){
		c = fgetc(fn);
		if(c == 0){
			break;
		}
		decryptedWord[lastIndex] = (char)(c);
		lastIndex++;
	}
	//close the file
	fclose(fn);
	--lastIndex;
	int start = lastIndex;
	int caps = 1;
	while(decrypt(decryptedWord,lastIndex,start,caps) != 1){
		--start;
		if(start == -1){
			caps = 0;
			start = lastIndex;
		}
	}
}
