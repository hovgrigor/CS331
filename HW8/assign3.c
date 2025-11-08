#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  char path[256];
  int fd;
  off_t size;
  char byte;

  printf("Enter file path: ");
  if (scanf("%s", path) != 1) {
    perror("reading file path");
    return 1;
  }

  fd = open(path, O_RDONLY);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  size = lseek(fd, 0, SEEK_END);
  if (size < 0) {
    perror("lseek SEEK_END");
    close(fd);
    return 1;
  }

  if (size == 0) {
    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    return 0;
  }

  for (off_t pos = size - 1; pos >= 0; pos--) {
    if (lseek(fd, pos, SEEK_SET) < 0) {
      perror("lseek SEEK_SET");
      close(fd);
      return 1;
    }

    if (read(fd, &byte, 1) != 1) {
      perror("read");
      close(fd);
      return 1;
    }

    if (write(STDOUT_FILENO, &byte, 1) != 1) {
      perror("write");
      close(fd);
      return 1;
    }
  }

  write(STDOUT_FILENO, "\n", 1);

  close(fd);
  return 0;
}
