#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  const char *filename = "numbers.txt";
  const char *tempfile = "numbers.tmp";
  int fd_in, fd_out;
  char buffer[10];
  ssize_t nread;
  int line_number = 0;

  fd_in = open(filename, O_RDONLY);
  if (fd_in < 0) {
    perror("open original");
    return 1;
  }

  fd_out = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd_out < 0) {
    perror("open temp");
    close(fd_in);
    return 1;
  }

  ssize_t i = 0;
  char line[10];
  ssize_t line_len = 0;
  while ((nread = read(fd_in, buffer, 1)) > 0) {
    line[line_len++] = buffer[0];

    if (buffer[0] == '\n') {
      line[line_len] = '\0';
      line_number++;

      if (line_number == 4) {
        const char *new_line = "100\n";
        if (write(fd_out, new_line, strlen(new_line)) !=
            (ssize_t)strlen(new_line)) {
          perror("write temp");
          close(fd_in);
          close(fd_out);
          return 1;
        }
      } else {
        if (write(fd_out, line, line_len) != line_len) {
          perror("write temp");
          close(fd_in);
          close(fd_out);
          return 1;
        }
      }

      line_len = 0;
    }
  }

  close(fd_in);
  close(fd_out);

  if (rename(tempfile, filename) < 0) {
    perror("rename");
    return 1;
  }

  fd_in = open(filename, O_RDONLY);
  if (fd_in < 0) {
    perror("open for read");
    return 1;
  }
  while ((nread = read(fd_in, buffer, sizeof(buffer))) > 0) {
    if (write(STDOUT_FILENO, buffer, nread) != nread) {
      perror("write stdout");
      close(fd_in);
      return 1;
    }
  }
  if (nread < 0)
    perror("read final");

  close(fd_in);
  return 0;
}
