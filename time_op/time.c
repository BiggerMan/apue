#include <stdio.h>
#include <time.h>

int main()
{
	time_t now;
	struct tm *current;

	time(&now);
	current = gmtime(&now);//time_t to struct tm
	printf("just now time is:%02d-%02d-%02d:%02d:%02d:%02d\n"
			,1900+current->tm_year,//start from 1900
			1+current->tm_mon,//start from 0,0-11
			current->tm_mday,//1-31
			current->tm_hour,//0-23
			current->tm_min,//0-59
			current->tm_sec);//0-60

	current = localtime(&now);//
	
	return 0;
}
