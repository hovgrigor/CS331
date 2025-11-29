#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

long long balance = 0;
int DEPOSITS = 4;
int WITHDRAWS = 4;
long long OPERATIONS = 500;

pthread_mutex_t mtx;
pthread_spinlock_t spin;

int use_mutex = 1; // 1=mutex, 0=spin
int long_cs = 0;   // 1=long CS, 0=short CS

static inline void lock() {
  if (use_mutex)
    pthread_mutex_lock(&mtx);
  else
    pthread_spin_lock(&spin);
}

static inline void unlock() {
  if (use_mutex)
    pthread_mutex_unlock(&mtx);
  else
    pthread_spin_unlock(&spin);
}

void *deposit_thread(void *arg) {
  for (long long i = 0; i < OPERATIONS; i++) {
    lock();
    balance++;
    if (long_cs)
      usleep(100); // Simulate long operation
    unlock();
  }
  return NULL;
}

void *withdraw_thread(void *arg) {
  for (long long i = 0; i < OPERATIONS; i++) {
    lock();
    balance--;
    if (long_cs)
      usleep(100);
    unlock();
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./assign_2.c <mutex or spin> <short or long>\n");
    return 1;
  }

  // lock type
  if (strcmp(argv[1], "mutex") == 0)
    use_mutex = 1;
  else if (strcmp(argv[1], "spin") == 0)
    use_mutex = 0;
  else {
    printf("Invalid lock type.\n");
    return 1;
  }

  // critical section length
  if (strcmp(argv[2], "short") == 0)
    long_cs = 0;
  else if (strcmp(argv[2], "long") == 0)
    long_cs = 1;
  else {
    printf("Invalid CS type.\n");
    return 1;
  }

  // init lock
  if (use_mutex)
    pthread_mutex_init(&mtx, NULL);
  else
    pthread_spin_init(&spin, 0);

  pthread_t threads[8];

  // create threads
  for (int i = 0; i < DEPOSITS; i++)
    pthread_create(&threads[i], NULL, deposit_thread, NULL);

  for (int i = 0; i < WITHDRAWS; i++)
    pthread_create(&threads[DEPOSITS + i], NULL, withdraw_thread, NULL);

  // join
  for (int i = 0; i < DEPOSITS + WITHDRAWS; i++)
    pthread_join(threads[i], NULL);

  if (use_mutex)
    pthread_mutex_destroy(&mtx);
  else
    pthread_spin_destroy(&spin);

  printf("Final balance: %lld\n", balance);
  return 0;
}
