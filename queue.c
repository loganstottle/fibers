#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "fiber.h"
#include "queue.h"

void queue_init(queue_t* q) {
  q->bottom = q->top = 0;
  q->capacity = 1 << 16;
  q->fibers = malloc(q->capacity * sizeof(fiber_t*));
  mtx_init(&q->lock, mtx_plain);
}

ptrdiff_t queue_size(queue_t* q) {
  return (ptrdiff_t)q->bottom - (ptrdiff_t)q->top;
}

void queue_push_bottom(queue_t* q, fiber_t* f) {
  mtx_lock(&q->lock);
  if (queue_size(q) >= (ptrdiff_t)q->capacity - 1) {
    printf("fatal: full run queue %zu/%zu\n", queue_size(q), q->capacity);
    exit(1);
  }

  q->fibers[q->bottom++ % q->capacity] = f;
  mtx_unlock(&q->lock);
}

fiber_t* queue_pop_bottom(queue_t* q) {
  mtx_lock(&q->lock);
  q->bottom--;

  if (queue_size(q) < 0) {
    q->bottom = q->top;
    mtx_unlock(&q->lock);
    return NULL;
  }

  fiber_t* f = q->fibers[q->bottom % q->capacity];
  mtx_unlock(&q->lock);
  return f;
}

fiber_t* queue_pop_top(queue_t* q) {
  mtx_lock(&q->lock);

  if (q->bottom - q->top <= 0) {
    mtx_unlock(&q->lock);
    return NULL;
  }

  fiber_t* f = q->fibers[q->top % q->capacity];

  mtx_unlock(&q->lock);
  return f;
}
