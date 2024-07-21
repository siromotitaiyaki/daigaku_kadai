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
  addi a2, zero, 1 // load text length
  ecall
  lw t2, 0(t0)
  addi t3, zero, 49
  addi t4, zero, 50
  beq t2, t3, iftrue1
  beq t2, t4, iftrue2
else:
  la s0, str03
  li s1, str03_length
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, s0, 0 // load text address
  addi a2, s1, 0 // load text length
  ecall
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  la s0, str04
  li s1, str04_length
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, s0, 0 // load text address
  addi a2, s1, 0 // load text length
  ecall
  j end_loop
iftrue1:
  la s0, str01
  li s1, str01_length
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, s0, 0 // load text address
  addi a2, s1, 0 // load text length
  ecall
  j end_loop
iftrue2:
  la s0, str02
  li s1, str02_length
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, s0, 0 // load text address
  addi a2, s1, 0 // load text length
  ecall
end_loop:
  ebreak
  j end_loop

.data
  array_1: .space 12
  str01: .ascii "1 has been inputted\n"
  str02: .ascii "2 has been inputted\n"
  str03: .ascii "It is neither 1 nor 2\n"
  str04: .ascii " has been inputted\n"
  str_sentinel:
  .equ str01_length, str02 - str01
  .equ str02_length, str03 - str02
  .equ str03_length, str04 - str03
  .equ str04_length, str_sentinel - str04

#pragma qtrvsim tab core