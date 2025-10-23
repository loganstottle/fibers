.intel_syntax noprefix

.globl ctx_switch
.type ctx_switch, @function

ctx_switch:
  mov [rdi + 0],  rbx
  mov [rdi + 8],  rbp
  mov [rdi + 16], rsp
  mov [rdi + 24], r12
  mov [rdi + 32], r13
  mov [rdi + 40], r14
  mov [rdi + 48], r15

  mov rbx, [rsi + 0]
  mov rbp, [rsi + 8]
  mov rsp, [rsi + 16]
  mov r12, [rsi + 24]
  mov r13, [rsi + 32]
  mov r14, [rsi + 40]
  mov r15, [rsi + 48]
  mov rdi, [rsi + 56]

  ret

.section .note.GNU-stack,"",@progbits
