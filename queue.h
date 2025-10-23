#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <threads.h>

#include "fiber.h"

typedef struct {
  size_t top, bottom, capacity;
  fiber_t** fibers;
  mtx_t lock;
} queue_t;

void queue_init(queue_t* q);
ptrdiff_t queue_size(queue_t* q);
void queue_push_bottom(queue_t* q, fiber_t* f);
fiber_t* queue_pop_bottom(queue_t* q);
fiber_t* queue_pop_top(queue_t* q);

#endif
