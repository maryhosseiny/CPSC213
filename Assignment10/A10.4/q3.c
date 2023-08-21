#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_THREADS 3
uthread_t threads[NUM_THREADS];
uthread_mutex_t mutex;
uthread_cond_t doneCondition;
int threads_ran;

void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void waitForAllOtherThreads() {
  while (threads_ran != NUM_THREADS) {
    uthread_cond_wait(doneCondition);
  }
  uthread_cond_broadcast(doneCondition);
}

void* p(void* v) {
  randomStall();
  uthread_mutex_lock(mutex);
  printf("a\n");
  threads_ran++;
  waitForAllOtherThreads();
  uthread_mutex_unlock(mutex);
  printf("b\n");
  return NULL;
}

int main(int arg, char** arv) {
  uthread_init(4);
  mutex = uthread_mutex_create();
  doneCondition = uthread_cond_create(mutex);
  for (int i=0; i<NUM_THREADS; i++)
    threads[i] = uthread_create(p, NULL);
  for (int i=0; i<NUM_THREADS; i++)
    uthread_join (threads[i], NULL);
  printf("------\n");
}