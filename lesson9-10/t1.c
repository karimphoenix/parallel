#include <stdio.h>
#include <pthread.h>

#define NTHREADS 100

void *thread_function(void *);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

long int  counter = 0;

main()
{
	long int ttime1;
	long int ttime2;
	long int ttime;

	ttime1 = time(NULL);

	pthread_t thread_id[NTHREADS];

	int i, j;

	for(i=0; i < NTHREADS; i++)

	{
		printf("поток №%d открыт\n", i+1);
		pthread_create( &thread_id[i], NULL, thread_function, NULL );
		

	}

	 

	for(j=0; j < NTHREADS; j++)

	{

		pthread_join( thread_id[j], NULL);

	}

	   

	   /* Now that all threads are complete I can print the final result.     */

	   /* Without the join I could be printing a value before all the threads */

	   /* have been completed.                                                */

	 

	printf("Final counter value: %li\n", counter);
	ttime2 = time(NULL);
	ttime = ttime2 - ttime1;
	printf("Программа работала: %li секунд\n", ttime);

}

	 

void *thread_function(void *dummyPtr)

{
//	printf("Thread number %ld\n", pthread_self());

	//pthread_mutex_lock( &mutex1 );
	
	int i=0;
	for (; i<10000; ++i){
		pthread_mutex_lock( &mutex1 );
		counter++;
		pthread_mutex_unlock( &mutex1 );
		usleep(1);
	}

	//pthread_mutex_unlock( &mutex1 );
}