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
  char r[2];
  char str[200];
  
  key = ftok("/home/Work16/file", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if (data)
    printf("Shared Memory Segment was just created\n");
  else {
    printf("Segment contains: %s\n", data);
  }
  printf("Do you want to change the data in the segment? (y/n)\n");
  fgets(r, 2, stdin);
  if (strcmp(r, "y") == 0) {
    printf("Enter a new string:\n");
    fgets(str, 200, stdin);
    strncpy(data, str, 200);
  } 

  printf("Do you want to delete the segment? (y/n)\n");
  fgets(r, 2, stdin);
  if (strcmp(r, "y") == 0) {
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
  }
  
  return 0;
}
  
