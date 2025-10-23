#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <stdbool.h>
#include <unistd.h>

#include "sched.h"
#include "worker.h"
#include "queue.h"

queue_t globalq;
worker_t workers[NUM_WORKERS];

void sched() {
  queue_init(&globalq);

  for (int i = 0; i < NUM_WORKERS; i++) {
    workers[i].id = i;
    workers[i].globalq = &globalq;

    if (thrd_create(&workers[i].thread, work, &workers[i])) {
      printf("fatal: failed to create thread %d...", i);
      exit(1);
    }
  }

  spawn(fmain, NULL);

  while (true) sleep(1);
}

void sched_spawn(char* name, void(*fn)(void*), void *arg) {
  printf("\"%s\" spawned...\n", name);
  queue_push_bottom(&globalq, fiber_create(name, fn, arg));
}

int main() {
  sched();
  __builtin_unreachable();
}
