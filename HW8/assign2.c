#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  const char *filename = "data.txt";
  int fd;
  ssize_t bytes_written, bytes_read;
  char buffer[64];
  off_t size;

  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("open for write");
    return 1;
  }

  bytes_written = write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
  if (bytes_written < 0) {
    perror("write");
    close(fd);
    return 1;
  }

  close(fd);

  fd = open(filename, O_RDWR);
  if (fd < 0) {
    perror("open for read/write");
    return 1;
  }

  size = lseek(fd, 0, SEEK_END);
  if (size < 0) {
    perror("lseek SEEK_END");
    close(fd);
    return 1;
  }
  printf("Current size: %ld bytes\n", (long)size);

  if (ftruncate(fd, 10) < 0) {
    perror("ftruncate");
    close(fd);
    return 1;
  }

  size = lseek(fd, 0, SEEK_END);
  if (size < 0) {
    perror("lseek SEEK_END after truncate");
    close(fd);
    return 1;
  }
  printf("New size after truncate: %ld bytes\n", (long)size);

  if (lseek(fd, 0, SEEK_SET) < 0) {
    perror("lseek SEEK_SET");
    close(fd);
    return 1;
  }

  bytes_read = read(fd, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    perror("read");
    close(fd);
    return 1;
  }

  buffer[bytes_read] = '\0';
  printf("Remaining content: \"%s\"\n", buffer);

  close(fd);
  return 0;
}
