#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi t1, zero, 65
  sw t1, 0(t0)
  li s0, 8
  li s1, 6
  li s4, 10
  add s2, s0, s1
  sub s3, s0, s1
  div s5, s2, s4
  mul s6, s4, s5
  sub s6, s2, s6
  div s7, s3, s4
  mul s8, s4, s7
  sub s8, s3, s8
  addi s5, s5, 48
  sw s5, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  addi s6, s6, 48
  sw s6, 0(t0)
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
  addi s7, s7, 48
  sw s7, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  addi s8, s8, 48
  sw s8, 0(t0)
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
end_loop:
  ebreak
  j end_loop

.data
  array_1: .space 12
  array_2: .ascii "\n"

#pragma qtrvsim tab core