#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int N;

void *thread_hello(void *threadid) 
{
	long tid;
       	tid = (long)threadid;	
	printf("Hello SCR. Written by thread ID: %ld\n", tid);
	pthread_exit(NULL);
}





int main(int arc, char* argv[])
{

N = atoi(argv[1]);

pthread_t id[N];

int rc;

for(int i = 0; i<N; i++)
{
	rc = pthread_create(&id[i], NULL, thread_hello, i);
}

for(int i = 0; i<N; i++)
{
	pthread_join(id[i], NULL);
}

pthread_exit(NULL);

return 0;
}
