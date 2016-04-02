#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* you can just comment this line and see what will happen. */
#define USE_MUTEX

#ifdef USE_MUTEX
static pthread_mutex_t mutex;
#endif
static int number;

static void *producer(void *param)
{
	int i;

#ifdef USE_MUTEX
	pthread_mutex_lock(&mutex);
#endif
	printf("I'm in critical\n");
	for (i = 0; i < 1000000; i++)
		number++;
	printf("I'm out\n");

#ifdef USE_MUTEX
	pthread_mutex_unlock(&mutex);
#endif
	pthread_exit(0);
}

static void *consumer(void *param)
{
	int i;

#ifdef USE_MUTEX
	pthread_mutex_lock(&mutex);
#endif
	printf("I'm in critical\n");
	for (i = 0; i < 1000000; i++)
		number--;
	printf("I'm out\n");
#ifdef USE_MUTEX
	pthread_mutex_unlock(&mutex);
#endif
	pthread_exit(0);
}

int main(void)
{
	pthread_attr_t attr;
	pthread_t producer_tid, consumer_tid;

	pthread_attr_init(&attr);
#ifdef USE_MUTEX
	pthread_mutex_init(&mutex, NULL);
#endif

	pthread_create(&producer_tid, &attr, consumer, NULL);
	pthread_create(&consumer_tid, &attr, producer, NULL);

	pthread_join(producer_tid, NULL);
	pthread_join(consumer_tid, NULL);

	printf("%d\n", number);

	return 0;
}
