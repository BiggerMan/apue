#include "mylib.h"

int main()
{
	char buff[MAXSTRLEN];
	//
	printf("@");
	while(fgets(buff, MAXSTRLEN, stdin) != NULL)
	{
		buff[strlen(buff)-1] = '\0';
		if(strcmp(buff,"ls")==0)
		{
			do_ls(1,"");	
		}
		else
		{
			printf("unknown command!\n");
		}
		printf("@");
	}
	printf("program exit!\n");

	exit(0);
}

