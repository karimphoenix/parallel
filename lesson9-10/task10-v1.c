#include <stdio.h>
#include <time.h>
#include <stdint.h>

long int count;

//Incrementation global variable
void increment()
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

	count = 0;
	int i;
	for (i = 0; i < 100; ++i)
	{
        increment();
	}

	printf("Result count = %li\n", count);

	//result time
	ttimeend = time(NULL);
	ttime = ttimeend - ttimestart;

	printf("Program works: %li seconds\n", ttime);

	return 0;
}
