#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

void create_file(char *path) {
  int file = open(path, O_CREAT | O_TRUNC, 0644);
  close(file);
}

int get_file_size(char *path) {
  struct stat file_stats;
  stat(path, &file_stats);
  return file_stats.st_size;
}

void print_file(char *path) {
  int file_size = get_file_size(path);
  char string[file_size + 1];
  string[file_size] = '\0';
  int file = open(path, O_RDONLY);
  read(file, string, file_size);
  close(file);
  printf("%s", string);
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    if (!strcmp(argv[1], "create")) {
      int shmid = shmget(2187, sizeof (char[10000]), IPC_CREAT | IPC_RMID | 0644);
      printf("created shared memory %d\n", shmid);
      char *shm = shmat(shmid, NULL, 0);
      *shm = '\0';
      shmdt(shm);
      create_file("story.txt");
      printf("created story.txt\n");
    }
    else if (!strcmp(argv[1], "remove")) {
      int shmid = shmget(2187, sizeof (int), 0);
      shmctl(shmid, IPC_RMID, 0);
      printf("removed shared memory %d\n", shmid);
      printf("contents of story:\n");
      print_file("story.txt");
    }
  }
  return 0;
}
