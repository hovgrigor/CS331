#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main() {
  char path1[256];
  char path2[256];
  int src_fd, dest_fd;
  ssize_t bytes_read, bytes_written;
  char buffer[BUFFER_SIZE];
  long total_bytes = 0;

  printf("Enter source file path: ");
  if (scanf("%s", path1) != 1) {
    perror("reading source path");
    return 1;
  }

  printf("Enter destination file path: ");
  if (scanf("%s", path2) != 1) {
    perror("reading destination path");
    return 1;
  }

  src_fd = open(path1, O_RDONLY);
  if (src_fd < 0) {
    perror("open source");
    return 1;
  }

  dest_fd = open(path2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (dest_fd < 0) {
    perror("open destination");
    close(src_fd);
    return 1;
  }

  while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
    bytes_written = write(dest_fd, buffer, bytes_read);
    if (bytes_written < 0) {
      perror("write");
      close(src_fd);
      close(dest_fd);
      return 1;
    }
    total_bytes += bytes_written;
  }

  if (bytes_read < 0) {
    perror("read");
    close(src_fd);
    close(dest_fd);
    return 1;
  }

  close(src_fd);
  close(dest_fd);

  printf("Copied %ld bytes successfully.\n", total_bytes);

  return 0;
}
