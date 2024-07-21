#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi t1, zero, 65
  sw t1, 0(t0)
  addi s4, zero, 10 // null
  addi s5, zero, 48 // 0
  addi s6, s5, 9 // 9
  addi s7, zero, 1
  addi s8, zero, 9 //keta
  addi a7, zero, 63 // load syscall "read" number
  addi a0, zero, 0 // load file descriptor (0 = stdin)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
loop_head1:
  ecall
  lw s3, 0(t0)
  beq s3, s4, iftrue
  blt s3, s5, not_number
  blt s6, s3, not_number
  sub s3, s3, s5
  mul s1, s1, s4
  add s1, s1, s3
  j loop_head1
iftrue:
  addi s2, zero, 0
  addi s0, zero, 1
loop_head2:
  blt s1, s0, keta
  add s2, s2, s0
  addi s0, s0, 2
  j loop_head2
keta:
  addi s8, s8, -1
  beq s8, zero, output
  mul s7, s7, s4
  j keta
output: // s2
  la t0, array_1
  addi t1, zero, 65
  sw t1, 0(t0)
  div s9, s2, s7
  mul s10, s7, s9
  sub s2, s2, s10
  div s7, s7, s4
  addi s9, s9, 48
  sw s9, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  bge zero, s7, end_loop
  j output
not_number:
  la s0, str
  li s1, str_length
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
  str: .ascii "Not Number\n"
  str_sentinel:
  .equ str_length, str_sentinel - str

#pragma qtrvsim tab core