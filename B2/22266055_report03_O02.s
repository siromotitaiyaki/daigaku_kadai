#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  la t0, array_1
  addi s4, zero, 10 // null
  addi s5, zero, 32 // " "
  addi a7, zero, 63 // load syscall "read" number
  addi a0, zero, 0 // load file descriptor (0 = stdin)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  jal ra, routine00 // be mul num load
  addi s2, t1, 0
  jal ra, routine00 // mul num load
  addi s3, t1, 0
  sw s5, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  ecall
  ecall
mul_num: // width
  addi t3, t3, 1
  addi s6, t3, 48
  sw s6, 0(t0)
  ecall
  beq s3, t3, enter
  sw s5, 0(t0)
  ecall
  ecall
  j mul_num
enter: // output enter & be mul num
  jal ra, routine01
  blt s2, t2, end_loop
  addi s7, t2, 48
  sw s7, 0(t0)
  addi a1, t0, 0
  ecall
  addi t3, zero, 1
be_mul_num: // length
  sw s5, 0(t0)
  addi a7, zero, 64 // load syscall "write" number
  addi a0, zero, 1 // load file descriptor (1 = stdout)
  addi a1, t0, 0 // load text address
  addi a2, zero, 1 // load text length
  ecall
  mul t4, t2, t3
  div t5, t4, s4
  beq t5, zero, space_bit
else: // case 2bit
  mul t6, t5, s4
  sub t4, t4, t6
  addi t5, t5, 48
  sw t5, 0(t0)
  ecall
  j one_bit
space_bit: // case 1bit
  sw s5, 0(t0)
  ecall
one_bit: // lowest bit
  addi t4, t4, 48
  sw t4, 0(t0)
  ecall
  addi t3, t3, 1
  blt s3, t3, enter
  j be_mul_num

end_loop:
  ebreak
  j end_loop

routine00:
  ecall
  lw t1, 0(t0)
  addi t1, t1, -48
  jalr zero, 0(ra)
routine01:
  la t1, array_2
  addi a1, t1, 0
  ecall
  addi t2, t2, 1
  jalr zero, 0(ra)

.data
  array_1: .space 12
  array_2: .ascii "\n"

#pragma qtrvsim tab core