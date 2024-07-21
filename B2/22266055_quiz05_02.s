#pragma qtrvsim show terminal
#pragma qtrvsim show registers
#pragma qtrvsim show csrdock
#pragma qtrvsim show memory

.globl縲main
main:
  addi s1, zero, 100
  addi s2, zero, 0
  addi s0, zero, 1
loop_head:
  add s2, s2, s0
  bge s0, s1, end_loop
  addi s0, s0, 1
  j loop_head
end_loop:
  ebreak #Please see register s2
  j end_loop

#pragma qtrvsim tab core