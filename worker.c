#include <stdbool.h>
#include <unistd.h>

#include "worker.h"

int work(void* arg) {
  worker_t* w = arg;

  while (true) {
    fiber_t* f = queue_pop_bottom(w->globalq);
    if (f) fiber_resume(f, w);
  }

  __builtin_unreachable();
}
