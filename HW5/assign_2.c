#include <stdio.h>
#include <stdlib.h>

void printArr(int *arr, int n, char message[]) {
  printf("%s", message);
  for (int i = 0; i < n; i++) {
    printf("%d ", *(arr + i));
  }
}

int main() {
  int n = 0;
  int sum = 0;
  printf("Enter arr size -> ");
  scanf("%d", &n);

  int *arr = calloc(n, sizeof(int));
  if (arr == NULL) {
    printf("Not good\n");
    return 1;
  }
  printArr(arr, n, "Array after calloc: ");

  printf("\nEnter %d integers:\n", n);
  for (int i = 0; i < n; i++) {
    printf("arr[%d] -> ", i);
    scanf("%d", &arr[i]);
    sum += arr[i];
  }

  printArr(arr, n, "Updated array: ");
  printf("\nAverage of the array: %d\n", sum / n);
  free(arr);
  return 0;
}
