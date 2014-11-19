#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char * argv[])
{	
	// create the pipe
  	int fd[2];
 	pipe(fd);

	// fork
  	int pid=fork();
	
	// father
	if (pid != 0)
	{
		// write into the pipe
   		close(fd[0]);
		dup2(fd[1],1);		
		execlp("who","who",NULL);
	}

	// son
	else
	{
		close(fd[1]);
		dup2(fd[0],0);
		execlp("grep","grep",argv[1],NULL);
	}

	return 0;
}
