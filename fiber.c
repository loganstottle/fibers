#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ucontext.h>

#include "fiber.h"
#include "worker.h"

worker_t* current_worker = NULL;
fiber_t* current_fiber = NULL;

fiber_t* fiber_create(char* name, void(*fn)(void*), void* arg) {
  fiber_t* result = malloc(sizeof(fiber_t));
  result->name = name;

  result->stack = malloc(FIBER_STACK_SIZE);

  getcontext(&result->context);
  result->context.uc_stack.ss_sp = result->stack;
  result->context.uc_stack.ss_size = FIBER_STACK_SIZE;

  makecontext(&result->context, (void(*)())fiber_trampoline, 2, fn, arg);

  return result;
}

void fiber_resume(fiber_t* f, void* w) {
  worker_t* ww = (worker_t*) w;

  current_worker = ww;
  current_fiber = f;

  swapcontext(&ww->context, &f->context);
}

void fiber_yield() {
  queue_push_bottom(current_worker->globalq, current_fiber);
  printf("\"%s\" yielded...\n", current_fiber->name);
  swapcontext(&current_fiber->context, &current_worker->context);
  printf("resuming \"%s\"...\n", current_fiber->name);
}

void fiber_trampoline(void(*fn)(void*), void* arg) {
  printf("starting \"%s\"...\n", current_fiber->name);
  fn(arg);
  printf("\"%s\" done...\n", current_fiber->name);
  swapcontext(&current_fiber->context, &current_worker->context);
  __builtin_unreachable();
}
