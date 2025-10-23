#include <stdio.h>

#include "sched.h"

void print(void* arg) {
  printf("arg=%s\n", (char*) arg);
}

void fmain() {
  spawn(print, "hello");
  for (int i = 0; i < 1000; i++) {
    yield;
  }
  spawn(print, "world");
}
