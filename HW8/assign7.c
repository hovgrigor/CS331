#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  char path1[256], path2[256];
  int fd1, fd2;
  ssize_t n1, n2;
  unsigned char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
  off_t byte_index = 0;

  printf("Enter first file path: ");
  if (scanf("%s", path1) != 1) {
    perror("reading first file path");
    return 1;
  }

  printf("Enter second file path: ");
  if (scanf("%s", path2) != 1) {
    perror("reading second file path");
    return 1;
  }

  fd1 = open(path1, O_RDONLY);
  if (fd1 < 0) {
    perror("open first file");
    return 1;
  }

  fd2 = open(path2, O_RDONLY);
  if (fd2 < 0) {
    perror("open second file");
    close(fd1);
    return 1;
  }

  while (1) {
    n1 = read(fd1, buf1, BUFFER_SIZE);
    if (n1 < 0) {
      perror("read first file");
      close(fd1);
      close(fd2);
      return 1;
    }

    n2 = read(fd2, buf2, BUFFER_SIZE);
    if (n2 < 0) {
      perror("read second file");
      close(fd1);
      close(fd2);
      return 1;
    }

    ssize_t min_read = n1 < n2 ? n1 : n2;
    for (ssize_t i = 0; i < min_read; i++) {
      if (buf1[i] != buf2[i]) {
        printf("Files differ at byte %ld\n", (long)(byte_index + i));
        close(fd1);
        close(fd2);
        return 1;
      }
    }

    byte_index += min_read;

    if (n1 != n2) {
      printf("Files differ at byte %ld\n", (long)byte_index);
      close(fd1);
      close(fd2);
      return 1;
    }

    if (n1 == 0)
      break;
  }

  printf("Files are identical\n");
  close(fd1);
  close(fd2);
  return 0;
}
