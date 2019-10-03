#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define buffer 1024

typedef struct ArrStruct
{
	char* fn; //File name
	char s; //symbol
	int f; //Flag(0-true, 1-false)
	int k; //count
} Arr;

void* edit_struc(void *args)
{
	Arr *arr = (Arr*) args;

	//w/r variable
	ssize_t rb;
	int fd;

	//open file
	fd = open( arr->fn , O_RDONLY);
	if (fd < 0)
	{
		arr->f = 1;
            perror("open"); //error
		exit(1);
	}

	//count our symbol in file
	char l[buffer+1];
	int j;

	while ((rb = read(fd, l, buffer)) > 0)
	{
		for( j=0; j<buffer+1; j++)
		{
			if ((arr->s) == l[j]) (arr->k)++; //counts
		}
	}

	//close file
	if (rb < 0)
	{
		arr->f = 1;
            perror("Error: ");
	}

	if (close (fd) != 0)
	{
		arr->f = 1;
            perror("Error: ");
		exit(1);
	}
}

int main(int argn, char *argv[])
{

	//current time
	long int ttimestart;
	long int ttimeend;
	long int ttime;

	ttimestart = time(NULL);

	//Threads
	pthread_t * threads;
	Arr * arr;
	int status;
    int status_addr;
	int i;

	srand(time(NULL));

	//memory for array of struct
	if((arr = malloc((argn-1)*sizeof(Arr))) == NULL)
	{
		printf("Segmentation fault\n");
        exit(1);
	}

	//memory for threads
	if((threads = malloc((argn-1)*sizeof(pthread_t))) == NULL)
	{
		printf("Segmentation fault\n");
        exit(1);
	}

	//modified structure
	char c = 'a'+rand()%26;
	for (i = 0; i < argn-1; i++)
	{
		arr[i].fn = argv[i+1];
		arr[i].s = c;
		arr[i].f = 0;
		arr[i].k = 0;
	}

	//Create threads
	for (i = 0; i < argn-1; i++)
	{

		status = pthread_create(&threads[i], NULL, edit_struc, (void*) &arr[i]);
        if (status != 0)
        {
        	exit(-1);
   		}
	}

   	//lock treads
   	for (i = 0; i < argn-1; i++)
   	{
		status = pthread_join(threads[i], (void**)&status_addr);
		if (status != 0)
		{
                perror("pthread_join");
			exit(-2);
        }
	}

	//Output
	for (i = 0; i < argn-1; i++)
	{
 	   	printf("Structure array[%d]: %s %c %d %d\n", i+1, arr[i].fn, arr[i].s, arr[i].f, arr[i].k);
	}


	ttimeend = time(NULL);
	ttime = ttimeend - ttimestart;
	printf("Program work: %li seconds\n", ttime);

	return 0;
}
