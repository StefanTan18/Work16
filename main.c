#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>

int main() {
  key_t key;
  int shmid;
  char *data;
  char r[200];
  
  key = ftok("file", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if (!data[0])
    printf("Shared Memory Segment was just created\n");
  else {
    printf("Segment contains: %s\n", data);
  }
  printf("Do you want to change the data in the segment? (y/n)\n");
  fgets(r, 200, stdin);
  if (!strcmp(r, "y\n")) {
    printf("Enter a new string:\n");
    fgets(r, 200, stdin);
    strcpy(data, r);
  } 

  printf("Segment contains: %s\n", data);
  
  printf("Do you want to delete the segment? (y/n)\n");
  fgets(r, 200, stdin);
  
  if (!strcmp(r, "y\n")) {
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Segment deleted.\n");
  }
  else {
    printf("Segment was not deleted.\n");
  }
  return 0;
}
  
