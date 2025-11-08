#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  const char *filename = "sparse.bin";
  int fd;
  off_t size;

  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("open for write");
    return 1;
  }

  if (write(fd, "START", 5) != 5) {
    perror("write START");
    close(fd);
    return 1;
  }

  if (lseek(fd, 1024 * 1024, SEEK_CUR) < 0) {
    perror("lseek");
    close(fd);
    return 1;
  }

  if (write(fd, "END", 3) != 3) {
    perror("write END");
    close(fd);
    return 1;
  }

  close(fd);

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    perror("open for read");
    return 1;
  }

  size = lseek(fd, 0, SEEK_END);
  if (size < 0) {
    perror("lseek SEEK_END");
    close(fd);
    return 1;
  }

  printf("Apparent file size: %ld bytes\n", (long)size);

  close(fd);
  return 0;
}

/*
Explanation:
This program creates a sparse file. The lseek() call moves the file
offset far beyond the current end without writing data which leaves a
hole in the file that the filesystem doesn’t physically allocate.
When viewed with ls -l, the size appears large,
but du -h sparse.bin will report much less disk usage since no actual
blocks were allocated for the skipped region.
*/
