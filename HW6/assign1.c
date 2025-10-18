#include <stdio.h>

int main() {
  int a = 1;
  char b = 'A';
  double c = 3.1415;
  short d = 2;

  printf("Size of int: %zu bytes\n", sizeof(a));
  printf("Size of char: %zu bytes\n", sizeof(b));
  printf("Size of double: %zu bytes\n", sizeof(c));
  printf("Size of short: %zu bytes\n\n", sizeof(d));

  printf("Address of int a: %p\n", (void *)&a);
  printf("Address of char b: %p\n", (void *)&b);
  printf("Address of double c: %p\n", (void *)&c);
  printf("Address of short d: %p\n", (void *)&d);

  return 0;
}
