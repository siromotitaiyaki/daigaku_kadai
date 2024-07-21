#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi s4, zero, 10 // null
  addi s5, zero, 1000 //keta
  addi a7, zero, 63 // load syscall "read" number
  addi a0, zero, 0 // load file descriptor (0 = stdin)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  jal ra, routine00 // number1 read
  addi s2, t2, 0
  jal ra, routine00 // number2 read
  addi s3, t2, 0
  blt s3, s2, replace // compare
return:
  addi s0, s2, 0
  addi s1, s2, 0
loop:
  addi s8, s0, 0
  jal ra, routine01 // number being calculated
  addi s1, s1, 1
  add s0, s0, s1
  beq s1, s3, output
  j loop
output: // result number
  addi s5, zero, 1000 //keta
output_loop:
  div s6, s0, s5
  mul s7, s5, s6
  sub s0, s0, s7
  div s5, s5, s4
  addi s6, s6, 48
  sw s6, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  beq s5, zero, end_loop
  j output_loop
end_loop:
  ebreak
  j end_loop

routine00:
  ecall
  lw s3, 0(t0)
  addi s3, s3, -48
  add t2, zero, s3
  mul t2, t2, s4
  ecall
  lw s3, 0(t0)
  addi s3, s3, -48
  add t2, t2, s3
  jalr zero, 0(ra)
routine01:
  addi s5, zero, 1000 //keta
routine01_loop:
  div s6, s8, s5
  mul s7, s5, s6
  sub s8, s8, s7
  div s5, s5, s4
  addi s6, s6, 48
  sw s6, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  beq s5, zero, return01
  j routine01_loop
return01:
  la t2, array_2
  addi a7, zero, 64
  addi a0, zero, 1
  addi a1, t2, 0
  addi a2, zero, 1
  ecall
  jalr zero, 0(ra)
replace:
  addi t2, s2, 0
  addi s2, s3, 0
  addi s3, t2, 0
  j return

.data
  array_1: .space 12
  array_2: .ascii "\n"

#pragma qtrvsim tab core