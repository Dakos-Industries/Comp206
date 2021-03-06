#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void printMonth(char* days[], char month [], int length, int* wsp){
	// this method will print out the specified month
	// it will be called 12 times
	//Prints out the star character on one line
	int i = 0;
	for (i = 0; i < 22; i++){
		printf("*");
	}
	for (i = 0; i < (length*7); i++){
		printf("*");
	}
	//Prints out the month
	printf("\n* %s \n" , month);	

	for (i = 0; i < 22; i++){
		printf("*");
	}
	for (i = 0; i < (length*7); i++){
		printf("*");
	}
	
	printf("\n");	
	//printing day names
	for(i=0; i < 7; i++){
		printf("* %.*s ",length, days[i]);
		int d = length - strlen(days[i]);
		if (d > 0){
			int count = 0;
			for (count; count < d; count++){
				printf(" ", d);
			}
		}
	}

	printf("*\n");
	for (i = 0; i < 22; i++){
		printf("*");
	}
	for (i = 0; i < (length*7); i++){
		printf("*");
	}
	
	printf("\n");	
	// printing out day numbers
	int dayCount = 1;

	for(i=1; i <= 7; i++){	
		
		if(i < *wsp){
			printf("*  %*s",length," ");
		}else if (i == *wsp){
			printf("* %d ",dayCount);
			int j = 0;
			int x = 0;

			if (dayCount < 10){
				x =1;
			}else{x =2; }

			for (j = 0; j < (length - x); j++){
				printf(" ");
			}
			++dayCount;
		}else {
			printf("* %d ",dayCount);
			int w = 0;
			int x = 0;
			if (dayCount < 10){
				x =1;
			}else{x =2; }
	
			for (w = 0; w < (length- x); w++){
				printf(" ");
			}
			
			++dayCount;	
		}
		
	}
	printf("*\n");
	// prints out rest of the day numbers and makes sure we don't go over 30 days
	for(i; i <= 35; i++){
		if (dayCount < 31){
				printf("* %d ",dayCount);
			int w = 0;
			int x = 0;
			if (dayCount < 10){
				x =1;
			}else{x =2; }
	
			for (w = 0; w < (length- x); w++){
				printf(" ");
			}
			
			++dayCount;	
	
		}else{
			printf("*  %*s",length," ");
	
		}
		if ((i%7) == 0){
			printf("*\n");
		}
	} 
	// used to get starting day of the next month
	*wsp = (*wsp + 2);
	if (*wsp > 7){
		*wsp = (*wsp - 7);
	}

}

void main(int argc, char* argv[]){

	// not enough argument error
	if(argc < 4){
		printf("ERROR: INVALID INPUT; not enough arguments");
		exit(0);
	}
	int length = atoi(argv[2]); // gets the string length
	int weekStart = atoi(argv[3]); // gets the day of the week 
	// error handling for string length and week start 
	if(length < 2){
		printf("ERROR:INVALID INPUT");
		exit(0);
	}else if( weekStart > 7 || weekStart <= 0){
		printf("ERROR:INVALID INPUT");
		exit(0);	
	}
	
	// Strings as char [] for the days of the week and the months
	char mon[10], tue[10], wed[10] , th[10], fri[10], sat[10],sun[10];
	
	char jan[10], feb[10], mar[10], apr[10],may[10],jun[10],jul[10],
	     aug[10], sep[10], oct[10], nov[10], dec[10];	

	// oepns the file and gets the name of the days and months
	// in the specified language

	FILE *fp ;
	//error checking if file exists 
	if (access(argv[1],F_OK) != -1){
		//exist
	}else{
		printf("ERROR: INVALID INPUT");
		exit(0);
	}
	fp = fopen(argv[1], "r");	
	if(fp == NULL){
		printf("ERROR: INVALID INPUT");
		exit(0);
	}
	
	fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		,sun, mon, tue, wed, th, fri, sat, 
		jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec);

	char* days[] = {sun,mon,tue,wed,th,fri,sat};
	char* months[] = {jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	// prints the months out. calls printMonth 12 times.
	printMonth(days, jan, length, &weekStart);	
	printMonth(days, feb, length, &weekStart); 
	printMonth(days, mar, length, &weekStart);	
	printMonth(days, apr, length, &weekStart); 
	printMonth(days, may, length, &weekStart);	
	printMonth(days, jun, length, &weekStart); 
	printMonth(days, jul, length, &weekStart);	
	printMonth(days, aug, length, &weekStart); 
	printMonth(days, sep, length, &weekStart);	
	printMonth(days, oct, length, &weekStart); 
	printMonth(days, nov, length, &weekStart);	
	printMonth(days, dec, length, &weekStart); 
	
}
