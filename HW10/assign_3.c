#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

int P = 2;
int C = 2;
int K = 20;
int total_items;

int produced = 0;
int consumed = 0;

pthread_mutex_t buffer_mutex;
pthread_mutex_t count_mutex;

sem_t empty_slots;
sem_t full_slots;

void *producer(void *arg) {
  while (1) {
    pthread_mutex_lock(&count_mutex);
    if (produced >= total_items) {
      pthread_mutex_unlock(&count_mutex);
      return NULL;
    }
    int item = produced;
    produced++;
    pthread_mutex_unlock(&count_mutex);

    sem_wait(&empty_slots);

    pthread_mutex_lock(&buffer_mutex);
    buffer[in_pos] = item;
    in_pos = (in_pos + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&buffer_mutex);

    sem_post(&full_slots);
  }
}

void *consumer(void *arg) {
  while (1) {
    pthread_mutex_lock(&count_mutex);
    if (consumed >= total_items) {
      pthread_mutex_unlock(&count_mutex);
      return NULL;
    }
    consumed++;
    pthread_mutex_unlock(&count_mutex);

    sem_wait(&full_slots);

    pthread_mutex_lock(&buffer_mutex);
    int item = buffer[out_pos];
    out_pos = (out_pos + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&buffer_mutex);

    sem_post(&empty_slots);
  }
}

int main() {
  total_items = P * K;

  pthread_mutex_init(&buffer_mutex, NULL);
  pthread_mutex_init(&count_mutex, NULL);
  sem_init(&empty_slots, 0, BUFFER_SIZE);
  sem_init(&full_slots, 0, 0);

  pthread_t prod[P], cons[C];

  for (int i = 0; i < P; i++)
    pthread_create(&prod[i], NULL, producer, NULL);

  for (int i = 0; i < C; i++)
    pthread_create(&cons[i], NULL, consumer, NULL);

  for (int i = 0; i < P; i++)
    pthread_join(prod[i], NULL);

  for (int i = 0; i < C; i++)
    pthread_join(cons[i], NULL);

  pthread_mutex_destroy(&buffer_mutex);
  pthread_mutex_destroy(&count_mutex);
  sem_destroy(&empty_slots);
  sem_destroy(&full_slots);

  printf("Produced: %d, Consumed: %d\n", produced, consumed);
  return 0;
}
