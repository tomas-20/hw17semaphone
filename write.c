#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char *get_shm_string(int key) {
  return shmat(shmget(key, 0, 0), NULL, 0);
}

void fill_with_input(char *string, int length) {
  fgets(string, length + 1, stdin);
}

void write_to_file(char *path, char *string) {
  int file = open(path, O_WRONLY | O_APPEND);
  dprintf(file, "%s", string);
  close(file);
}

int main() {
  char *shm = get_shm_string(2187);
  printf("the last line was:\n%syou are adding:\n", shm);
  fill_with_input(shm, 10000);
  write_to_file("story.txt", shm);
  shmdt(shm);
  return 0;
}
