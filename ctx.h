#ifndef CTX_H
#define CTX_H

#include <stdlib.h>

typedef struct {
  size_t rbx, rbp, rsp, r12, r13, r14, r15, rdi;
} ctx_t;

void ctx_switch(ctx_t* from, ctx_t* to);

#endif
