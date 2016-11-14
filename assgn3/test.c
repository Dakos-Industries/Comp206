#include <stdio.h>
#include <string.h>

void main(){

	FILE *a;
	a = fopen("a.txt", "r");
	char *c;
	while (scanf("%s ",c) != 10){
		printf("%s",c);
	}

}
