#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argn, char ** argv){
	if(argn!=2){
		printf("Usage: %s имя_фаила\n", argv[0]);
	}
	srand(time(NULL));
	char * fn = argv[1];
	FILE * f = fopen(fn, "w");
	int i;
	char * str = malloc(110000000+1);
	int j;
	for(j = 0;j<110000000; ++j)
	{
		str[j] = 'a'+rand()%26;
	}
	str[110000000] = '\0';
	fprintf(f,"%s\n", str);
}