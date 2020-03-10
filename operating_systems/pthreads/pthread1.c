#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 50

void* hello(void *a)
{
	int num = *(int *)a;
	printf("Oi, thread %d\n", num); 
	return 0;
}

int main()
{
	int i;
	pthread_t th[NUM_THREADS];

	for(i = 0; i < NUM_THREADS; i++){
		pthread_create(&th[i], NULL, hello, &i);
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(th[i], NULL);
	}

	return 0;
}
