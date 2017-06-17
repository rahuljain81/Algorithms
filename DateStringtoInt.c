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

int diffdays(int,int,int,int,int,int);
int month(int,int);
int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};


int main()
{
	char date[MAX_DATE+1];
	int year, month, day, hour, minutes;
	int syear, smonth, sday, shour, sminutes;
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
	
	sscanf (START_DATE, "%04d%02d%02d%02d%02d", &syear, &smonth, &sday, &shour, &sminutes);
	startdate = syear * 10000 + smonth * 100 + sday;
	starttime = shour * 100 + sminutes;
	printf ("%d %d\n", startdate, starttime); 

	printf ("Diff %d\n", idate-startdate);

	//To Calculate Days between two dates
	printf("The no. of days b/w the 2 dates = %d days\n", diffdays (syear, year, smonth, month, sday, day));


	{
		//To check overlap of dates/time
		//https://stackoverflow.com/questions/325933/determine-whether-two-date-ranges-overlap
		//(StartA <= EndB) && (StartB <= EndA)

		//Same Date: A) Start Time 0830 End Time 1130
		// B) Start Time 1030 End Time 1330
		int overlap = (830 <= 1330) && (1030 <= 1130);
		printf ("Overlap %d\n", overlap);

	}

	return 0;
}

int diffdays(int y1,int y2,int m1,int m2,int d1,int d2)
{
	int count=0,i;

	//Max Number of days 0101YYYY to 0101(YYYY+1)
	for(i=y1;i<y2;i++)
	{
		if(i%4==0)
			count+=366;
		else
			count+=365;
	}

	//Substract number of months & days gone in start date
	count-=month(m1,y1);
	count-=d1;

	//Add number of months & days in end date after the year
	count+=month(m2,y2);
	count+=d2;

	if(count<0)
		count=count*-1;

	return count;
}

int month(int month,int yy)
{
	int days=0,c;
	for(c=0;c<month-1;c++)
	{
		if(c==1)
		{
			if(yy%4==0)
				days+=29;
			else
				days+=28;
		}
		else
			days+=mon[c];
	}
	return(days);
}

