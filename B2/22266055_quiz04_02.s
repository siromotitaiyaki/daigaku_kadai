#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi t1, zero, 65
  sw t1, 0(t0)
  addi a7, zero, 63 // load syscall "read" number
  addi a0, zero, 0 // load file descriptor (0 = stdin)
  addi a1, t0, 0 // load text address
  addi a2, zero, 10 // load text length
  ecall
  addi s0, a0, 0
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  add a2, zero, s0 // load text length
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