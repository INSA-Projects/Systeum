#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


pid_t pidFils;  

void creer10 ()
{
	int i = 0;
	for (i=0;i<9;i++)
	{
		pidFils = fork();
		if (pidFils == 0)
		{
			i=10;
		}
	}
}

main(){
  pidFils = fork();
  if (pidFils!=0){
    /* ------------ code du p�re ----------------- */
      printf("je suis le pere\n");
      sleep(1);
    

  }
  else{
    /* ------------ code du fils ----------------- */
    int i;
    creer10();
    printf("je suis le fils\n");
    sleep(1);
    
  }

}


