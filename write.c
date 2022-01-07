#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
  int shmid = shmget(2187, sizeof (char[10000]), 0);
  char *shm = shmat(shmid, NULL, 0);
  printf("the last line was:\n%syou are adding:\n", shm);
  fgets(shm, 10000, stdin);
  shmdt(shm);
  int file = open("story.txt", O_WRONLY);
  printf("hola\n");
  printf(file, "%s", shm);
  dprintf(file, "%s", shm);
  return 0;
}
