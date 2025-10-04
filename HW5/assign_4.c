#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 3;

  char **arr = calloc(n, sizeof(char *));
  if (arr == NULL) {
    printf("Not good\n");
    return 1;
  }

  for (int i = 0; i < n; i++) {
    arr[i] = malloc(50 * sizeof(char));
    if (arr[i] == NULL)
      return 1;
  }

  printf("\nEnter %d strings:\n", n);
  for (int i = 0; i < n; i++) {
    printf("arr[%d] -> ", i);
    scanf("%49s", arr[i]);
  }
  int n_new = 5;
  arr = realloc(arr, n_new * sizeof(char *));
  if (arr == NULL) {
    printf("Not good\n");
    return 1;
  }

  for (int i = n; i < n_new; i++) {
    arr[i] = malloc(50 * sizeof(char));
    if (arr[i] == NULL)
      return 1;
  }

  printf("\nEnter %d new strings:\n", n_new - n);
  for (int i = n; i < n_new; i++) {
    printf("arr[%d] -> ", i);
    scanf("%49s", arr[i]);
  }

  printf("All strings: ");
  for (int i = 0; i < n_new; i++) {
    printf("%s ", arr[i]);
    free(arr[i]);
  }

  free(arr);
  return 0;
}
