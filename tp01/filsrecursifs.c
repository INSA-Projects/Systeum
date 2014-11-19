#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


pid_t pidFils;
int rang = 1;

void creerdeuxfils()
{
	pidFils = fork();
	
	if (pidFils!=0)
	{
    		/* ------------ code du père ----------------- */
      		printf("je suis de generation %d\n",rang);
     		sleep(1);
  	}

  	else
	{
    		/* ------------ code du fils ----------------- */
		rang++;
		if (rang<5)
		{
			pidFils = fork();
			creerdeuxfils();
		}
    		sleep(1);
  	}
}

main()
{
     creerdeuxfils();
}




