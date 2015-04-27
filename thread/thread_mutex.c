#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

struct Data
{
	pthread_mutex_t lock;
	int count;
};

int stop=0;
void* data_get(void *arg)
{
	struct Data *data = (struct Data *)arg;
	while(stop==0)
	{
		pthread_mutex_lock(&data->lock);
		printf("data:%d\n",data->count--);
		pthread_mutex_unlock(&data->lock);
		sleep(2);
	}
		
	return (void*)0;
}

void* data_release(void *arg)
{
	struct Data *data = (struct Data *)arg;
	int i=4;
	while(stop==0)
	{
		pthread_mutex_lock(&data->lock);
		printf("data:%d\n",data->count--);
		if(data->count <= 0)
		{
			pthread_mutex_unlock(&data->lock);
			pthread_mutex_destroy(&data->lock);
			stop=1;
		}
		else
		{
			sleep(1);
			pthread_mutex_unlock(&data->lock);
		}
	}

	return (void*)0;
}

int main(void)
{
	int errno;
	pthread_t ntid1;
	pthread_t ntid2;
	void *ret;
	struct Data *data=malloc(sizeof(struct Data));
	data->count=10;
	pthread_mutex_init(&data->lock,NULL);
	stop=0;

	errno = pthread_create(&ntid1,NULL,data_get,(void*)data);
	if(errno)
		perror("thread1 create error:");
	errno = pthread_create(&ntid2,NULL,data_release,(void*)data);
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
