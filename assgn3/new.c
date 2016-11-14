#include <stdio.h>

void main(){

	char tmp[1000];
	fgets(tmp,1000,stdin);
	printf("%s\n",tmp);
	fgets(tmp, 1000,stdin);
	printf("%s",tmp);
}
