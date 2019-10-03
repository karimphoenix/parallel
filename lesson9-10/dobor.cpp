#include <vector>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

    vector<int> V1;
    vector<int> V2;
    vector<int> ResultV;

typedef struct VectStructure{

    int curent_coord;
    int number_of_treads;
    //int somethink;

}VecStr;

void * SumVect (void * args)
{

    VecStr *SV = (VecStr*)args;

	ResultV[SV->curent_coord] = V1[SV->curent_coord % SV->number_of_treads]+
                                V2[SV->curent_coord % SV->number_of_treads];

    return NULL;
}

int main(int argn, char ** argnum)
{
    
    pthread_t * threads;
    VecStr *SVect;
    int status;
    int status_addr;

    //memory for structure
    if((SVect = new VecStr[10]) == NULL)
	{
		printf("Segmentation fault1\n");
        exit(1);
	}

    //memory for threads
	if((threads = new pthread_t[10]) == NULL)
	{
		printf("Segmentation fault2\n");
        exit(1);
	}


	//modifide structure
	int i,j;

	V1.resize(10);

	V2.resize(10);

	ResultV.resize(10);
	for (i=0; i<10; i++)
    {
  	V1[i]=i;
    	V2[i]=i;
        SVect[i].curent_coord=i;
        SVect[i].number_of_treads=10;
    }

    //create treads
    for (i=0; i<10; i++)
    {
	//SVect->curent_coord=i;
        status = pthread_create(&threads[i], NULL, SumVect, (void*) (SVect+ i));
        if (status != 0)
        {
        	exit(-1);
   		}
    }

    //lock treads
   	for (i = 0; i < 10; i++)
   	{
		status = pthread_join(threads[i], (void**)&status_addr);
		if (status != 0)
		{
                perror("pthread_join");
			exit(-2);
        }
	}

	//Output
	for (i = 0; i < 10; i++)
	{
 	   	printf("Structure array[%d]: %d %d %d\n", i+1, V1[i], V2[i], ResultV[i]);
	}

	return 0;
}
