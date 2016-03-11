.section .text

.globl svc
.type svc, @function
svc:
  lea ptr_table(%rip), %rsi
  mov (%rsi, %rdi, 8), %rax
  ret

.align 0x10
.globl svcQueryName
.type svcQueryName, @function
svcQueryName:
  lea str_table(%rip), %rax
  shl $4, %rdi
  add %rdi, %rax
  ret

.align 0x10
.globl svcRegister
.type svcRegister, @function
svcRegister:
  lea ptr_table(%rip), %rax
  mov %rsi, (%rax, %rdi, 8)
  lea str_table(%rip), %rax
  shl $4, %rdi
  add %rdi, %rax
  movq $0, (%rax)
  movq $0, 8(%rax)
  movb $0, %sil
  
  .L0:
    movb (%rdx), %dil
    cmpb $0, %dil
    jz .L1
    cmpb $15, %sil
    jz .L1
    movb %dil, (%rax)
    inc %rax
    inc %rdx
    inc %sil
    jmp .L0
.L1:
  ret

data:
  ptr_table: .zero 16*8
  str_table: .zero 16*16
