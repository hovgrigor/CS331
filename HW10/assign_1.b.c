#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

long long counter = 0;
long long M = 1000000;
int N = 4;

pthread_mutex_t mtx;

void *worker(void *arg) {
  for (long long i = 0; i < M; i++) {
    pthread_mutex_lock(&mtx);
    counter++;
    pthread_mutex_unlock(&mtx);
  }
  return NULL;
}

int main() {
  pthread_t *threads = malloc(sizeof(pthread_t) * N);

  pthread_mutex_init(&mtx, NULL);

  for (int i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, worker, NULL);

  for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);

  pthread_mutex_destroy(&mtx);

  long long expected = (long long)N * M;

  printf("Expected: %lld\n", expected);
  printf("Actual:   %lld\n", counter);

  free(threads);
  return 0;
}
