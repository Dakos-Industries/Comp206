#include <stdio.h>
#include <string.h>
void main(int argc, char *argv[]){

	int shift = atoi(argv[1]);
	FILE *fn;
	fn = fopen(argv[2],"r");
	if(fn == NULL){
		printf("ERROR");
		return;
	}
	int c;
	char word[1000];
	int i = 0;
	c = fgetc(fn);
	while(c != EOF){
		if (c == '\n'){
			i++;
			break;
		}
		word[i] = c + shift;
		c = fgetc(fn);
		++i;
	}	
	fclose(fn);
	fn = fopen(argv[2],"w");
	--i;
	char nullterm = word[i];
	--i;
	while(i >= 0){
		fputc(word[i],fn);
		i--;
	}
	fputc(nullterm,fn);
	fclose(fn);
}
