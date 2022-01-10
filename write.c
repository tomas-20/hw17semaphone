#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int get_semid(int key) {
  return semget(key, 1, 0);
}

void change_sem(int semid, int amount) {
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = amount;
  semop(semid, &sb, 1);
}

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
  int semid = get_semid(24601);
  change_sem(semid, -1);
  char *shm = get_shm_string(2187);
  printf("the last line was:\n%syou are adding:\n", shm);
  fill_with_input(shm, 10000);
  write_to_file("story.txt", shm);
  shmdt(shm);
  change_sem(semid, 1);
  return 0;
}
