#ifndef FIBER_H
#define FIBER_H

#include <stdbool.h>
#include <ucontext.h>

#define FIBER_STACK_SIZE 64 * 1024

typedef struct worker worker;

typedef struct {
  char* name;
  void* stack;
  ucontext_t context;
  worker* worker;
  bool done;
} fiber_t;

fiber_t* fiber_create(char* name, void(*fn)(void*), void* arg);
void fiber_resume(fiber_t* f, void* w);
void fiber_yield();
void fiber_trampoline(void(*fn)(void*), void* arg);

#endif
