#ifndef WORKER_H
#define WORKER_H

#include <threads.h>

#include "queue.h"
#include "ctx.h"

typedef struct {
  int id;
  thrd_t thread;
  ctx_t context;
  queue_t* globalq;
} worker_t;

int work(void* arg);

#endif
