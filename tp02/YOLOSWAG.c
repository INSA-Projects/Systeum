#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

int main (int argc, char * argv[])
{
	int i=0;
	while(1){
		sleep(1);
		i++;
		printf("%d", &i);
	}
}

