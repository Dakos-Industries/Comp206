#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

void printDate(){}


main(int argc, char *argv[]){

	char day[10], month[10], num[2] ,time[8], thing[3], year[4];
	// If nothing is piped send error
	if (isatty(fileno(stdin))){
		printf("Error: Date was not Piped \n");
		exit(0);
	}
	//getting input form pipe
	scanf ("%s", day);
	scanf ("%s", month);
	scanf ("%s", num);
	scanf ("%s", time);
	scanf ("%s", thing);
	scanf ("%s", year);

	// variables
	char mon[10], tue[10], wed[10] , th[10], fri[10], sat[10],sun[10];
	char jan[10], feb[10], mar[10], apr[10],may[10],jun[10],jul[10],
	     aug[10], sep[10], oct[10], nov[10], dec[10];	

	//Open file and get data from it
	FILE *fp;
	fp = fopen(argv[1], "r");
	// if it doesn't exist send an error
	if (fp == NULL){
		printf("ERROR: INVALID INPUT \n");
		exit(0);
	}	
	//getting the data
	fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		,sun, mon, tue, wed, th, fri, sat, 
		jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec);

 	// comparing the input and printing proper outpur
	if ( strncmp("Mon",day,3) == 0){

	
		printf("%s ",mon);
	}else if ( strncmp("Tue",day,3) == 0){

	
		printf("%s ",tue);
	}else if ( strncmp("Wed",day,3) == 0){

	
		printf("%s ",wed);
	}else if ( strncmp("Thu",day,3) == 0){

	
		printf("%s ",th);
	}else if ( strncmp("Fri",day,3) == 0){

	
		printf("%s ",fri);
	}else if ( strncmp("Sat",day,3) == 0){

	
		printf("%s ",sat);
	}else if ( strncmp("Sun",day,3) == 0){

	
		printf("%s ",sun);
	}else {
		printf("ERROR: INVALID INPUT");
		exit(0);
	}

	//same but for months
	if ( strncmp("Jan",month,3) == 0){

	
		printf("%s ",jan);
	}else if ( strncmp("Feb",month,3) == 0){

	
		printf("%s ",feb);
	}else if ( strncmp("Mar",month,3) == 0){

	
		printf("%s ",mar);
	}else if ( strncmp("Apr",month,3) == 0){

	
		printf("%s ",apr);
	}else if ( strncmp("May",month,3) == 0){

	
		printf("%s ",may);
	}else if ( strncmp("Jun",month,3) == 0){

	
		printf("%s ",jun);
	}else if ( strncmp("Jul",month,3) == 0){

	
		printf("%s ",jun);
	}else if ( strncmp("Aug",month,3) == 0){

	
		printf("%s ",aug);
	}else if ( strncmp("Sep",month,3) == 0){

	
		printf("%s ",sep);
	}else if ( strncmp("Oct",month,3) == 0){

	
		printf("%s ",oct);
	}else if ( strncmp("Nov",month,3) == 0){

	
		printf("%s ",nov);
	}else if ( strncmp("Dec",month,3) == 0){

	
		printf("%s ",dec);
	}else {
		printf("ERROR: INVALID INPUT");
		exit(0);
	}

	fclose(fp);
	printf("%s %s %s %s \n",num, time, thing, year);


}
