#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"

queue_t pending_read_queue;
int globalCount;
int result;

void interrupt_service_routine() {
  void* value;
  void* locCount;
  void (*callback) (void*, void*);
  queue_dequeue(pending_read_queue, &value, &locCount, &callback);
  callback(value, locCount);
}

void handleOtherReads(void *resultv, void *countv) {
  int* locCount = countv;
  globalCount--;
  int* result = resultv;

  if (*locCount <= 0) {
    printf("%d\n", *result);
    exit(EXIT_SUCCESS);
  } else {
    disk_schedule_read(result, *result);
    queue_enqueue(pending_read_queue, result, locCount, handleOtherReads);
  }
}

void handleFirstRead(void *resultv, void *countv) {
  int* locCount = countv;
  int* result = resultv;
  *locCount = *result;
  
  if (*locCount == 0) {
    printf("%d\n", *result);
    exit(EXIT_SUCCESS);
  } else {
    disk_schedule_read(result, *result);
    queue_enqueue(pending_read_queue, result, locCount, handleOtherReads);
  }
}

int main(int argc, char **argv) {
  // Command Line Arguments
  static char* usage = "usage: treasureHunt starting_block_number";
  int starting_block_number;
  char *endptr;
  if (argc == 2)
    starting_block_number = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();


  // Start the Hunt
  disk_schedule_read(&result, starting_block_number);
  queue_enqueue(pending_read_queue, &result, &globalCount, handleFirstRead);
  while (1); // infinite loop so that main doesn't return before hunt completes
}
