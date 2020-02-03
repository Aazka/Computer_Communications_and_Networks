#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

struct Details
{
	char *Name;
	char *RegNo;
};
void *Print(void *ptr)
{
	struct Details* D=(struct Details*) ptr;
	printf("Name %s \n",D->Name);
	printf("RegNo %s",D->RegNo);
	pthread_exit(NULL);
}
int main()
{
	pthread_t tid;
	struct Details *abc;
	abc=(struct Details *)malloc(sizeof(struct Details));
	abc->Name="Aazka";
	abc->RegNo="L1f16bscs0191";
	if(pthread_create(&tid,NULL,Print,(void*)abc)<0)
	{
		printf("Error\n");
	}
	pthread_join(tid,NULL);
}