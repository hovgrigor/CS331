#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int N = 5;

sem_t semA, semB, semC;

void *thread_A(void *arg) {
  for (int i = 0; i < N; i++) {
    sem_wait(&semA);
    printf("A %d\n", i);
    sem_post(&semB);
  }
  return NULL;
}

void *thread_B(void *arg) {
  for (int i = 0; i < N; i++) {
    sem_wait(&semB);
    printf("B %d\n", i);
    sem_post(&semC);
  }
  return NULL;
}

void *thread_C(void *arg) {
  for (int i = 0; i < N; i++) {
    sem_wait(&semC);
    printf("C %d\n", i);
    sem_post(&semA);
  }
  return NULL;
}

int main() {
  pthread_t tA, tB, tC;

  sem_init(&semA, 0, 1);
  sem_init(&semB, 0, 0);
  sem_init(&semC, 0, 0);

  pthread_create(&tA, NULL, thread_A, NULL);
  pthread_create(&tB, NULL, thread_B, NULL);
  pthread_create(&tC, NULL, thread_C, NULL);

  pthread_join(tA, NULL);
  pthread_join(tB, NULL);
  pthread_join(tC, NULL);

  sem_destroy(&semA);
  sem_destroy(&semB);
  sem_destroy(&semC);

  return 0;
}
