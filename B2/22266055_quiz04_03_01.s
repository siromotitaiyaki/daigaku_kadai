#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi t1, zero, 65
  sw t1, 0(t0)
  li s0, 5
  li s1, 3
  add s2, s0, s1
  sub s3, s0, s1
  addi s2, s2, 48
  sw s2, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  la t2, array_2
  addi a7, zero, 64
  addi a0, zero, 1
  addi a1, t2, 0
  addi a2, zero, 1
  ecall
  addi s3, s3, 48
  sw s3, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
end_loop:
  ebreak
  j end_loop

.data
  array_1: .space 12
  array_2: .ascii "\n"

#pragma qtrvsim tab core