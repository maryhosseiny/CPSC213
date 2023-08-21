#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

uthread_t t0, t1, t2;
uthread_mutex_t mutex;
uthread_cond_t first_cond;
uthread_cond_t sec_cond;
int done_one = 0;
int done_two = 0;

void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void* p0(void* v) {
  randomStall();
  uthread_mutex_lock(mutex);
  printf("zero\n");
  done_one = 1;
  uthread_cond_signal(first_cond);
  uthread_mutex_unlock(mutex);
  return NULL;
}

void* p1(void* v) {
  randomStall();
  uthread_mutex_lock(mutex);
  while (!done_one) {
    uthread_cond_wait(first_cond);
  }
  printf("one\n");
  done_two = 1;
  uthread_cond_signal(sec_cond);
  uthread_mutex_unlock(mutex);
  return NULL;
}

void* p2(void* v) {
  randomStall();
  uthread_mutex_lock(mutex);
  while (!done_two) {
    uthread_cond_wait(sec_cond);
  }
  printf("two\n");
  uthread_mutex_unlock(mutex);
  return NULL;
}

int main(int arg, char** arv) {
  uthread_init(4);
  mutex = uthread_mutex_create();
  first_cond = uthread_cond_create(mutex);
  sec_cond = uthread_cond_create(mutex);
  t0 = uthread_create(p0, NULL);
  t1 = uthread_create(p1, NULL);
  t2 = uthread_create(p2, NULL);
  randomStall();
  uthread_join (t0, NULL);
  uthread_join (t1, NULL);
  uthread_join (t2, NULL);
  printf("three\n");
  printf("------\n");
}
