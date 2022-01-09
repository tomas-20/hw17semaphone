#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

void create_shm_string(int key, int length) {
  int shmid = shmget(key, sizeof (char[length + 1]), IPC_CREAT | IPC_RMID | 0644);
  char *shm = shmat(shmid, NULL, 0);
  *shm = '\0';
  shmdt(shm);
  printf("created shared memory %d\n", shmid);
}

void create_file(char *path) {
  int file = open(path, O_CREAT | O_TRUNC, 0644);
  close(file);
  printf("created %s\n", path);
}

int get_file_size(char *path) {
  struct stat file_stats;
  stat(path, &file_stats);
  return file_stats.st_size;
}

void remove_shm(int key) {
  int shmid = shmget(key, 0, 0);
  shmctl(shmid, IPC_RMID, 0);
  printf("removed shared memory %d\n", shmid);
}

void print_file(char *path) {
  int file_size = get_file_size(path);
  char string[file_size + 1];
  string[file_size] = '\0';
  int file = open(path, O_RDONLY);
  read(file, string, file_size);
  close(file);
  printf("contents of %s:\n%s", path, string);
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    if (!strcmp(argv[1], "create")) {
      create_shm_string(2187, 10000);
      create_file("story.txt");
    }
    else if (!strcmp(argv[1], "remove")) {
      remove_shm(2187);
      print_file("story.txt");
    }
  }
  return 0;
}
