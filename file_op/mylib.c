#include "mylib.h"
#include <dirent.h>
#include <sys/stat.h>

char* get_file_type(struct stat buf)
{
	char *ptr;

	if(S_ISREG(buf.st_mode))
		ptr="regular";
	else if(S_ISDIR(buf.st_mode))
		ptr="directory";
	else if(S_ISCHR(buf.st_mode))
		ptr="character special";
	else if(S_ISBLK(buf.st_mode))
		ptr="block";
	else if(S_ISFIFO(buf.st_mode))
		ptr="fifo";
	else if(S_ISLNK(buf.st_mode))
		ptr="symbolic link";
	else if(S_ISSOCK(buf.st_mode))
		ptr="socket";
	else
		ptr="unknown";

	return ptr;
}

int do_ls(int argc,char *argv[])
{
	DIR *dp;
	struct stat state;
	struct dirent *dirp;
	char cwd[MAXPATHLEN];
	char *fullpath;
	char *ptr;
	int len;

	getcwd(cwd, MAXPATHLEN);
	fullpath = malloc(MAXPATHLEN);
	strncpy(fullpath, cwd, MAXPATHLEN);
	ptr = fullpath + strlen(fullpath);
	*ptr++='/';
	*ptr=0;

	if(argc==1)
	{
		if((dp=opendir(cwd)) == NULL )
		{
			perror("can't open current dir!");
		}
	}
	else if(argc==2)
	{	
		if((dp=opendir(argv[1])) == NULL )
		{
			perror("can't open current dir!");
		}

	}
	else
		printf("multi paths are not supported now!\n");
	/*print the dir list*/
	printf("name\t\ttype\n");
	while( (dirp=readdir(dp))!=NULL )
	{
		strcpy(ptr, dirp->d_name);
		lstat(fullpath, &state);
		printf("%s\t\t%s\n", dirp->d_name, get_file_type(state));
	}

	closedir(dp);

	return 0;
}


