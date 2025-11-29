#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int K = 3;
int N = 10;

sem_t printers;
pthread_mutex_t count_mutex;
int active = 0;

void *print_job(void *arg) {
  int id = (int)(long)arg;

  sem_wait(&printers);

  pthread_mutex_lock(&count_mutex);
  active++;
  printf("Thread %d START printing (active = %d)\n", id, active);
  pthread_mutex_unlock(&count_mutex);

  usleep(200000);

  pthread_mutex_lock(&count_mutex);
  active--;
  printf("Thread %d END printing (active = %d)\n", id, active);
  pthread_mutex_unlock(&count_mutex);

  sem_post(&printers);
  return NULL;
}

int main() {
  pthread_t threads[N];

  pthread_mutex_init(&count_mutex, NULL);
  sem_init(&printers, 0, K);

  for (int i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, print_job, (void *)(long)i);

  for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);

  sem_destroy(&printers);
  pthread_mutex_destroy(&count_mutex);

  return 0;
}
