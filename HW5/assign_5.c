#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 0;
  printf("Enter the number of students -> ");
  scanf("%d", &n);

  int *arr = malloc(n * sizeof(int));
  if (arr == NULL) {
    printf("Not good\n");
    return 1;
  }

  printf("Enter %d grades: \n", n);
  for (int i = 0; i < n; i++) {
    printf("arr[%d] -> ", i);
    scanf("%d", &arr[i]);
  }

  int max = arr[0];
  int min = arr[0];

  for (int i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
    if (arr[i] < min) {
      min = arr[i];
    }
  }

  printf("Highest grade: %d\n", max);
  printf("Lowest grade: %d\n", min);

  free(arr);
  return 0;
}
