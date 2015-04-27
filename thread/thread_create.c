#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

void printer(pthread_t tid)
{
	printf("tid is:%d\n",tid);
}

void* thread1(void *arg)
{
	pthread_t tid=pthread_self();
	printer(tid);
	int c1=10;
	while(c1>0)
	{
		printf("thread1 is running...\n");
		sleep(1);
		c1--;
	}

	return (void*)0;
}
void* thread2(void *arg)
{
	pthread_t tid=pthread_self();
	printer(tid);
	int c2=10;
	while(c2>0)
	{
		printf("thread2 is running...\n");
		sleep(1);
		c2--;
	}

	return (void*)0;
}


int main(void)
{
	int errno;
	pthread_t ntid1;
	pthread_t ntid2;
	void *ret;
	errno = pthread_create(&ntid1,NULL,thread1,NULL);
	if(errno)
		perror("thread1 create error:");
	errno = pthread_create(&ntid2,NULL,thread2,NULL);
	if(errno)
		perror("thread2 create error:");

	errno=pthread_join(ntid1,&ret);//main thread must wait two thread exit first
	if(errno)
		perror("thread1 exit error:");
	errno=pthread_join(ntid2,&ret);//otherwise, return 0 will kill both of them
	if(errno)
		perror("thread2 exit error:");

	//main thread is all a thread!!
	printf("main thread is going to end..\n");
	sleep(2);

	exit(0);
}
