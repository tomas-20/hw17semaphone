#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int shmid = shmget(2187, sizeof (char[10000]), 0);
  char *shm = shmat(shmid, NULL, 0);
  printf("the last line was:\n%syou are adding:\n", shm);
  fgets(shm, 10000, stdin);
  int file = open("story.txt", O_WRONLY | O_APPEND);
  dprintf(file, "%s", shm);
  close(file);
  shmdt(shm);
  return 0;
}
