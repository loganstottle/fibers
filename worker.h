#ifndef WORKER_H
#define WORKER_H

#include <threads.h>
#include <ucontext.h>

#include "queue.h"

typedef struct {
  int id;
  thrd_t thread;
  ucontext_t context;
  queue_t* globalq;
} worker_t;

int work(void* arg);

#endif
