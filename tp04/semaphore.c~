#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

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


void semP(int mysem){
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = -1; //1=V, -1=P
  op.sem_flg = 0;
  semop(mysem, &op, 1);
}


void semV(int mysem){
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


int main() 
{
  int semaphore = init(0);

  if (!fork()) 
  {
    semP(semaphore);
    deleteSem(semaphore);
  } 
   else
  {
    sleep(2);
    semV(semaphore);
  }    
  return 0;
}
