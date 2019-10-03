#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

long int count = 0;
//Increment global variable

void * increment()
{
	int i;
	for (i = 0; i < 10000; ++i)
	{
		count++;
		usleep(1);
	}
}

int main(int argn, char *argv[])
{
	//Time variable
	long int ttimestart;
	long int ttimeend;
	long int ttime;

	ttimestart = time(NULL);

	//Threads
	pthread_t *threads;
	int status;


	//memory for threads
	if((threads = malloc(100*sizeof(pthread_t))) == NULL)
	{
            printf("Segmentation fault\n");
        exit(1);
	}

	//Create threads
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

	//lock threads
   	for (i = 0; i < 100; i++)
   	{
		status = pthread_join(threads[i], NULL);
		if (status != 0)
		{
           		perror("Thread_join");
			exit(-2);
        	}
		//printf("Flow[%d] lock\n", i+1);
	}

	printf("Result count count = %li\n", count);

	//Result time
	ttimeend = time(NULL);
	ttime = ttimeend - ttimestart;

	printf("Program works: %li second\n", ttime);

	return 0;
}
