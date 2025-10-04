#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 0;
  int sum = 0;
  printf("Enter arr size -> ");
  scanf("%d", &n);

  int *arr = malloc(n * sizeof(int));
  if (arr == NULL) {
    printf("Not good\n");
    return 1;
  }

  printf("Enter %d integers: \n", n);
  for (int i = 0; i < n; i++) {
    printf("arr[%d] -> ", i);
    scanf("%d", &arr[i]);
    sum += arr[i];
  }

  printf("Sum: %d\n", sum);

  free(arr);
  return 0;
}
