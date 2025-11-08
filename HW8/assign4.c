#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  const char *filename = "log.txt";
  int fd;
  char input[BUFFER_SIZE];
  char output[BUFFER_SIZE + 64];
  ssize_t nread;
  pid_t pid;
  off_t offset;

  fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  printf("Enter a line to append: ");
  fflush(stdout);

  nread = read(STDIN_FILENO, input, sizeof(input) - 1);
  if (nread < 0) {
    perror("read");
    close(fd);
    return 1;
  }

  if (nread > 0 && input[nread - 1] == '\n') {
    input[nread - 1] = '\0';
  } else {
    input[nread] = '\0';
  }

  pid = getpid();
  snprintf(output, sizeof(output), "PID=%d: %s\n", pid, input);

  if (write(fd, output, strlen(output)) < 0) {
    perror("write");
    close(fd);
    return 1;
  }

  offset = lseek(fd, 0, SEEK_CUR);
  if (offset < 0) {
    perror("lseek");
    close(fd);
    return 1;
  }

  printf("Current file offset after append: %ld\n", (long)offset);

  close(fd);
  return 0;
}

/*
Explanation:
Even though the file is opened with O_APPEND, each write automatically moves the
file offset to the end before writing. However, the kernel still maintains and
updates the file’s logical offse. lseek(fd, 0, SEEK_CUR) returns the growing
offset position after each write reflecting.
*/
