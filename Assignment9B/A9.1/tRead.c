#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/errno.h>
#include <assert.h>
#include "queue.h"
#include "disk.h"
#include "uthread.h"

queue_t      pending_read_queue;
unsigned int sum = 0;

void interrupt_service_routine () {
  void* arg;
  queue_dequeue(pending_read_queue, &arg, NULL, NULL);
  uthread_unblock(arg);
}

void* read_block (void* blocknov) {
  int result;
  int* num_bloc = blocknov;
  uthread_t tempSum = uthread_self();
  queue_enqueue(pending_read_queue, tempSum, NULL, NULL);
  disk_schedule_read(&result, *num_bloc);
  uthread_block();
  sum = sum + result;
  return NULL;
}

int main (int argc, char** argv) {

  // Command Line Arguments
  static char* usage = "usage: tRead num_blocks";
  int num_blocks;
  char *endptr;
  if (argc == 2)
    num_blocks = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();

  // Sum Blocks
  int result[num_blocks];
  uthread_t threads [num_blocks];
  for (int blockno = 0; blockno < num_blocks; blockno++) {
    result[blockno] = blockno;
    threads[blockno] = uthread_create(read_block, &result[blockno]);
  }
  for (int blockno = 0; blockno < num_blocks; blockno++) {
    uthread_join(threads[blockno], 0);
  }
  printf("%d\n", sum);
}