#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define buffer 1024

typedef struct
{
	char* fn; //file name
	char s; //finder symbol
	int f; //flag
	int k; //count
} Arr;

void edit_struc(Arr *ar)
{
	//read/write variable
	ssize_t rb;
	int fd;

	//open file
	fd = open( (*ar).fn , O_RDONLY);
	if (fd < 0)
	{
		(*ar).f = 1;
            perror("open"); //errors
        exit(1);
	}

	//read to buffer
	char l[buffer+1];
	int j;

	while ((rb = read(fd, l, buffer)) > 0)
	{
		for( j=0; j<buffer+1; j++)
		{
			if (((*ar).s) == l[j]) ((*ar).k)++; //find symbol
		}
	}

	//close file
	if (rb < 0)
	{
		(*ar).f = 1;
            perror("Error: "); //errors
	}

	//close descriptor
	if (close (fd) != 0)
	{
		(*ar).f = 1;
            perror("Error: ");
		exit(1);
	}
}

int main(int argn, char *argv[])
{
	srand(time(NULL));

	// current time
	long int ttime1;
	long int ttime2;
	long int ttime;

	ttime1 = time(NULL);

	int i;

	//memory for struct
	Arr * arr;

	if((arr = malloc((argn-1)*sizeof(Arr))) == NULL)
	{
		printf("Segmentation fault\n");
        exit(1);
	}

	char c = 'a'+rand()%26;
	for (i = 0; i < argn-1; ++i)
	{
		arr[i].fn = argv[i+1];
		arr[i].s = c;
		arr[i].f = 0;
		arr[i].k = 0;

		edit_struc(&arr[i]);

		printf("Struct Arr[%d]: %s %c %d %d\n", i+1, arr[i].fn, arr[i].s, arr[i].f, arr[i].k);
	}

	ttime2 = time(NULL);
	ttime = ttime2 - ttime1;
	printf("Program time: %li seconds\n", ttime);

	return 0;

}
