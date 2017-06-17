#include <stdio.h>

#define MAX_DATE 8
#define MAX_TIME 4

#define START_DATE "200101010000"
#define INPUT_STR "201706172105"


void mystrncpy(char *dst, char *src, int n)
{
	while (n--)
		*dst++ = *src++;
}


int main()
{
	char date[MAX_DATE+1];
	int year, month, day, hour, minutes;
	int idate, itime, startdate, starttime;

	//mystrncpy (date, INPUT_STR, MAX_DATE);
	//date[MAX_DATE] = '\0';
	sscanf (INPUT_STR, "%8c", date);

	printf ("Date %s\n", date);
	//For Seperating string to seperate Integers
	sscanf (INPUT_STR, "%04d%02d%02d%02d%02d", &year, &month, &day, &hour, &minutes);
	idate = year * 10000 + month * 100 + day;
	itime = hour * 100 + minutes;
	printf ("%d %d\n", idate, itime); 
	
	sscanf (START_DATE, "%04d%02d%02d%02d%02d", &year, &month, &day, &hour, &minutes);
	startdate = year * 10000 + month * 100 + day;
	starttime = hour * 100 + minutes;
	printf ("%d %d\n", startdate, starttime); 

	printf ("Diff %d\n", idate-startdate);


	return 0;
}

