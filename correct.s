//this file contains all instructions, both data and text sections, all kinds of identation and 
//all kinds of labels and comments

.data	//this is data section
num: .word 123	#this is single integer
	array : .word 1, 2, 3, 4	// this is an array of integers
   string : .ascii "xyz"	#this is string
string1 : .asciiz "xyz1"	/this is null terminated string
		array1: .space 32	/this allocates space for label array1

		.text
main:
la $t0, array
  lw $t1, 0($t0)
lb $t2, 0($t0)
		sw $t1, 0($t0)
sb $t2, 0($t0)

L1:
  add $t2, $t0, $t1
addu $t2,$t0,	$t1
sub $t2, $t0, $t1
		subu $t2,$t0,$t1
slt $t3, $t0, $t1
	sltu $t3, $t0, 	$t1

L2:
and $s0, $t0, $t1
or $s0, $t0, $t1
xor $s0, $t0, $t1
nor $s0, $t0, $t1
sll $s1,	$t0,4
srl $s1,$t0,4
sra $s1,	$t0,4

L3:
	mult $s0, $t2
	multu $s0,$t2
	div $s0,    $t2
	mfhi $s7
	divu $s0,$t2
	mflo $t5
	addi $t0,  $t1,-1
	addiu $t0,$t1,1
	andi $t0, $t2, 2

L4:
ori $t0, $t2, 2
xori $t0, $t2, 2
lui $s3, 4000
slti $s8, $s4, -100
beq $s7,$s6,L1
bne $s7, $s8, L1
  blez $t5, L2
bgtz $t6, L2
bltz $t5, L3
  bgez $t6, L3
nop
	sltiu $t8, $t3, 100
	li $t3,6789
	li $t5, -12345
move $s2, $s4
j L1
jal L2
jalr $ra
jr $ra

exit:
li $v0,10
syscall