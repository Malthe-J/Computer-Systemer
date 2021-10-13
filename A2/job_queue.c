#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "job_queue.h"

int job_queue_init(struct job_queue *job_queue, int capacity) {
  struct job_queue q;
  job_queue_init(&q, 64);

  job_queue->Capacity = capacity;
  job_queue->arr[0] = NULL;
  struct job_queue *q = malloc(sizeof(struct job_queue)* capacity);
  
  for (int i = 0; i < capacity; i++)
  {
    job_queue->arr[i] = NULL;
  }
  
  return &q;
}

int job_queue_destroy(struct job_queue *job_queue) {
  assert(0);
}

int job_queue_push(struct job_queue *job_queue, void *data) {
  assert(0);
}

int job_queue_pop(struct job_queue *job_queue, void **data) {
  assert(0);
}
