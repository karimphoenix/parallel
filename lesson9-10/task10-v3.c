#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

//Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long int count = 0;

//increment function
void * increment()
{
	int i;
	for (i = 0; i < 10000; ++i)
	{
		pthread_mutex_lock( &mutex ); //mutex locked
		count++;
		pthread_mutex_unlock( &mutex ); //mutex unlocked
		usleep(1);
	}
}

int main(int argn, char *argv[])
{
	//timer variable
	long int ttimestart;
	long int ttimeend;
	long int ttime;

    //start timer
	ttimestart = time(NULL);

	//Treads
	pthread_t *threads;
	int status;


	//memory for threads
	if((threads = malloc(100*sizeof(pthread_t))) == NULL)
	{
            printf("Segmentation fault\n");
        exit(1);
	}

	//create threads
	int i;
	for (i = 0; i < 100; ++i)
	{
		status = pthread_create(&threads[i], NULL, increment, NULL);
    		if (status != 0)
    		{
        		exit(-1);
   		}
		//printf("Flow[%d] create\n", i+1);
	}

	//treads locked
   	for (i = 0; i < 100; i++)
   	{
		status = pthread_join(threads[i], NULL);
		if (status != 0)
		{
           		perror("Thread_join");
			exit(-2);
        	}
		//printf("Tread[%d] locked\n", i+1);
	}

	printf("Result count = %li\n", count);

	//Program time
	ttimeend = time(NULL);
	ttime = ttimeend - ttimestart;

	printf("Program works: %li seconds\n", ttime);

	return 0;

}
