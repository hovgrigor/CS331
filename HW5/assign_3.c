#include <stdio.h>
#include <stdlib.h>

void printArr(int *arr, int n, char message[]) {
  printf("%s", message);
  for (int i = 0; i < n; i++) {
    printf("%d ", *(arr + i));
  }
}

int main() {
  int n = 10;
  int sum = 0;

  int *arr = malloc(n * sizeof(int));
  if (arr == NULL) {
    printf("Not good\n");
    return 1;
  }

  printf("\nEnter %d integers:\n", n);
  for (int i = 0; i < n; i++) {
    printf("arr[%d] -> ", i);
    scanf("%d", &arr[i]);
  }

  arr = realloc(arr, 5 * sizeof(int));

  printArr(arr, 5, "Array after resizing: ");
  free(arr);
  return 0;
}
