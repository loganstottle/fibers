#ifndef SCHED_H
#define SCHED_H

#include "fiber.h"

#define NUM_WORKERS 8

void fmain();
void sched();
void sched_spawn(char* name, void(*fn)(void* arg), void *arg);

#define spawn(fn, arg) sched_spawn(#fn, fn, arg)
#define yield fiber_yield()

#endif
