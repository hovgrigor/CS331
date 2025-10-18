#include <stdio.h>

struct struct1 {
  int a;
  double b;
  char c;
};

#pragma pack(1)
struct pack1Struct {
  int a;
  double b;
  char c;
};

#pragma pack(2)
struct pack2Struct {
  int a;
  double b;
  char c;
};

#pragma pack(4)
struct pack4Struct {
  int a;
  double b;
  char c;
};

int main() {
  struct struct1 s1;
  struct pack1Struct s2;
  struct pack4Struct s3;
  struct pack4Struct s4;

  printf("=== Normal Struct (no packing) ===\n");
  printf("Size: %d bytes\n", (int)sizeof(s1));
  printf("Address of int: %p\n", (void *)&s1.a);
  printf("Address of double: %p\n", (void *)&s1.b);
  printf("Address of char: %p\n", (void *)&s1.c);

  printf("\n=== pack(1) ===\n");
  printf("Size: %zu bytes\n", sizeof(s2));
  printf("Address of int: %p\n", (void *)&s2.a);
  printf("Address of double: %p\n", (void *)&s2.b);
  printf("Address of char: %p\n", (void *)&s2.c);

  printf("\n=== pack(2) ===\n");
  printf("Size: %d bytes\n", (int)sizeof(s3));
  printf("Address of int: %p\n", (void *)&s3.a);
  printf("Address of double: %p\n", (void *)&s3.b);
  printf("Address of char: %p\n", (void *)&s3.c);

  printf("\n=== pack(4) ===\n");
  printf("Size: %d bytes\n", (int)sizeof(s4));
  printf("Address of int: %p\n", (void *)&s4.a);
  printf("Address of double: %p\n", (void *)&s4.b);
  printf("Address of char: %p\n", (void *)&s4.c);

  return 0;
}
