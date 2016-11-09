#include <stdio.h>
#include <string.h>
#include <unistd.h>

void main(int argc, char *argv[]){
	FILE *incoming, *outgoing;
	
	incoming = fopen(argv[1], "r");
	char incommsg[1000];
	int i = 0;
	char tmp[1000];
	while (fscanf(incoming,"%s",tmp) != EOF){
		i++;
		strcat(incommsg,tmp);
		strcat(incommsg," ");
	}
	if (i == 0){
		printf("Nothing Received Yet\n");
	}else{
		printf("Received: %s\n", incommsg);
	}	
	fclose(incoming);

	while(1){

		outgoing = fopen(argv[2],"w");	
		fputs("[",outgoing);
		fputs(argv[3],outgoing);
		fputs("] ",outgoing);
		printf("Send:");

		char c;
		c = getchar();
		while( c != '\n'){
			fputc(c,outgoing);
			c = getchar();
				
		}
		fclose(outgoing);
		sleep(2);	
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
				break;
			}
		}
		printf("Received: %s\n", incommsg);
		fclose(incoming);

		
	}
}
