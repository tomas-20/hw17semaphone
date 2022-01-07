#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    if (!strcmp(argv[1], "create")) {
      int shmid = shmget(2187, sizeof (char[10000]), IPC_CREAT | IPC_RMID | 0644);
      printf("created shared memory %d\n", shmid);
      char *shm = shmat(shmid, NULL, 0);
      *shm = '\0';
      shmdt(shm);
      int file = open("story.txt", O_CREAT | O_TRUNC, 0644);
      close(file);
    }
    else if (!strcmp(argv[1], "remove")) {
      int shmid = shmget(2187, sizeof (int), 0);
      shmctl(shmid, IPC_RMID, 0);
      printf("removed shared memory %d\n", shmid);
    }
  }
  return 0;
}
