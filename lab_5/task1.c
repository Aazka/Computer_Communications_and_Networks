#include<pthread.h>
#include<stdio.h>

void *Print(void *ptr)
{
	printf("Aazka Iqbal L1f16bscs0191\n");
	pthread_exit(NULL);
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,Print,NULL);
	/*
	if(pthread_create(&tid,NULL,Print,Null)<0)
	{
		printf("pthread not create");
	}*/
	pthread_join(tid,NULL);
}