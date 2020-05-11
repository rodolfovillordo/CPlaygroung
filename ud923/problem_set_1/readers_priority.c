#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define THREAD_MAX 5

int shared = 0;
int r_wait = 0;
int w_count = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_write = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_read = PTHREAD_COND_INITIALIZER;

void* reader(void* param);
void* writer(void* val);

int main(void)
{
	pthread_t r_ids[THREAD_MAX];
	pthread_t w_ids[THREAD_MAX];
	int i;
	int num = 0;
	for(i=0; i<THREAD_MAX; i++){
		/* Create writers threads */
		if(pthread_create(&w_ids[i], NULL, writer, &i)){
			printf("ERROR: creating producer %ld\n\n", w_ids[i]);
			exit(1);
		}
		/* Create readers threads */
		if(pthread_create(&r_ids[i], NULL, reader, NULL)){
			printf("ERROR: creating producer %ld\n\n", r_ids[i]);
			exit(1);
		}
	}

	for(i=0; i<THREAD_MAX; i++){
		pthread_join(w_ids[i], NULL);
		pthread_join(r_ids[i], NULL);
	}
}

void* writer(void* val)
{
	int rand;
	
	rand = random() % 10;
	/* sleep a random interval between 0..1 seconds */
	sleep(rand/10.0);
	pthread_mutex_lock(&m);
		while (r_wait > 0)
			pthread_cond_wait(&c_write, &m);
		w_count = 1;
		printf("\n\tWRITER shared: %d, val: %d, r_wait: %d\n", shared,
			       	rand, r_wait);
		shared = rand;
		w_count = 0;
	pthread_mutex_unlock(&m);
	pthread_cond_broadcast(&c_read);
}		

void* reader(void* param)
{
	int rand;

	rand = random() % 10;
	/* sleep a random interval between 0..1 seconds */
	sleep(rand/10.0);
	r_wait++;
	pthread_mutex_lock(&m);
		while(w_count > 0)
			pthread_cond_wait(&c_read, &m);
		printf("\n\tREADER shared=%d, r_wait=%d\n", shared, r_wait);
		r_wait--;
	pthread_mutex_unlock(&m);
	pthread_cond_signal(&c_write);
}
