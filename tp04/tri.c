#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <time.h> 


int init(int a)
{
  int mysem = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int retval;
  if(mysem < 0) perror("Error: semget");
  union semun
  {
    int val;
    struct semid_ds *buf;
    ushort *array;
  } arg;
  arg.val = a;  // Valeur d'initialisation
  retval = semctl(mysem, 0, SETVAL, arg);
  if(retval < 0) perror("Error: semctl");
  return mysem;
}


void semP(int mysem)
{
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = -1; //1=V, -1=P
  op.sem_flg = 0;
  semop(mysem, &op, 1);
}


void semV(int mysem)
{
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = 1; //1=V, -1=P
  op.sem_flg = 0;
  semop(mysem, &op, 1);
}

void deleteSem(int mysem)
{
  int retval = semctl(mysem, 0, IPC_RMID, NULL);
  if(retval < 0) perror("Error: semctl");  
}


void fusion(int tableau[],int deb1,int fin1,int fin2)
{
        int *table1;
        int deb2=fin1+1;
        int compt1=deb1;
        int compt2=deb2;
        int i;
        
        table1=malloc((fin1-deb1+1)*sizeof(int));

        //on recopie les éléments du début du tableau
        for(i=deb1;i<=fin1;i++)
            {
            table1[i-deb1]=tableau[i];
            }
                        
        for(i=deb1;i<=fin2;i++)
            {        
            if (compt1==deb2) //c'est que tous les éléments du premier tableau ont été utilisés
                {
                break; //tous les éléments ont donc été classés
                }
            else if (compt2==(fin2+1)) //c'est que tous les éléments du second tableau ont été utilisés
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute les éléments restants du premier tableau
                compt1++;
                }
            else if (table1[compt1-deb1]<tableau[compt2])
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute un élément du premier tableau
                compt1++;
                }
            else
                {
                tableau[i]=tableau[compt2]; //on ajoute un élément du second tableau
                compt2++;
                }
            }
        free(table1);
}


void triFusion (int* tab, int n)
{
	if (n > 1)
	{
		if(n/2>5) {
			int semaphore = init(0);
			if (!fork())
			{
				semP(semaphore);
				fusion(&tab[0], 0, n/2, n);
			}
			else 
			{
				triFusion(&tab[0], n/2);
				triFusion(&tab[n/2], n/2);
				semV(semaphore);
			}
		}
		else
		{
			triFusion(&tab[0], n/2);
			triFusion(&tab[n/2], n/2);			
			fusion(&tab[0], 0, n/2, n);
		}
	}
}


int main() 
{
	int n = 20;
	int tab[n];
	int i = 0;
	for(i=0; i<n; i++)
	{
		tab[i] = rand()%10;	
	}
	
 	triFusion(tab, n);

	for (i=0;i<n; i++)
	{
		printf("%d\n",&tab[i]);
	}

  return 0;
}






