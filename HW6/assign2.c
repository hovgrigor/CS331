#include <stdio.h>

struct struct1 {
  char a;
  int b;
  double c;
};

struct struct2 {
  int c;
  double b;
  char a;
};

int main() {
  struct struct1 s1;
  struct struct2 s2;

  printf("=== Struct 1 (char, int, double) ===\n");
  printf("Size of struct: %d bytes\n", (int)sizeof(s1));
  printf("Address of char: %p\n", (void *)&s1.a);
  printf("Address of int: %p\n", (void *)&s1.b);
  printf("Address of double: %p\n", (void *)&s1.c);

  printf("\n=== Struct 2 (int, double, char) ===\n");
  printf("Size of struct: %d bytes\n", (int)sizeof(s2));
  printf("Address of int: %p\n", (void *)&s2.c);
  printf("Address of double: %p\n", (void *)&s2.b);
  printf("Address of char: %p\n", (void *)&s2.a);

  return 0;
}
