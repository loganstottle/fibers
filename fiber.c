#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "fiber.h"
#include "worker.h"
#include "ctx.h"

worker_t* current_worker = NULL;
fiber_t* current_fiber = NULL;

fiber_t* fiber_create(char* name, void(*fn)(void*), void* arg) {
  fiber_t* result = malloc(sizeof(fiber_t));
  result->name = name;
  result->stack = malloc(FIBER_STACK_SIZE);

  size_t* sp = (size_t*)((size_t)result->stack + FIBER_STACK_SIZE);
  *(--sp) = (size_t)fiber_done;
  *(--sp) = (size_t)fn;

  result->context.rsp = (size_t)sp;
  result->context.rdi = (size_t)arg;

  return result;
}

void fiber_resume(fiber_t* f, void* w) {
  worker_t* ww = (worker_t*) w;

  current_worker = ww;
  current_fiber = f;

  ctx_switch(&ww->context, &f->context);
}

void fiber_yield() {
  queue_push_bottom(current_worker->globalq, current_fiber);
  ctx_switch(&current_fiber->context, &current_worker->context);
}

void fiber_done() {
  ctx_switch(&current_fiber->context, &current_worker->context);
  __builtin_unreachable();
}
