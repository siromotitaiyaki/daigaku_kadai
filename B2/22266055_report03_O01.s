#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi s3, zero, 1
  addi s4, zero, 10 // null
  addi s5, zero, 31 // bit_num
  addi s6, zero, 2
  addi s7, zero, 45 // "-"
  addi s8, zero, 0 // num
  addi s10, zero, 48 // "0"
  addi a7, zero, 63 // load syscall "read" number
  addi a0, zero, 0 // load file descriptor (0 = stdin)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
loop_head: // input num
  ecall
  lw s2, 0(t0)
  beq s2, s7, minus
  beq s2, s4, bit
  addi s2, s2, -48
  mul s0, s0, s4
  add s0, s0, s2
  j loop_head
minus:
  addi s9, s9, 1 // minus(s9=1)
  j loop_head
bit:
  blt s0, s3, output1
  jal ra, routine00
  j bit
output1: // bit filling
  sub s5, s5, s8
  addi s9, s9, 48
output1_loop:
  sw s9, 0(t0)
  addi s5, s5, -1
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  bge zero, s5, output2
  j output1_loop
output2: // binary
  beq s9, s10, output2_loop
else:
  addi s0, s0, -1
output2_loop:
  div s1, s0, s3
  mul t2, s1, s3
  sub s0, s0, t2
  div s3, s3, s6
  addi s1, s1, 48
  beq s9, s10, plus
else: // minus
  beq s1, s10, hosu // complement
else:
  addi s1, s1, -1
  j plus
hosu:
  addi s1, s1, 1
plus:
  sw s1, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  bge zero, s3, end_loop
  j output2_loop
end_loop:
  ebreak
  j end_loop

routine00:
  mul s3, s3, s6
  addi s8, s8, 1
  jalr zero, 0(ra)

.data
  array_1: .space 12

#pragma qtrvsim tab core