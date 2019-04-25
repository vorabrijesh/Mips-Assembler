//this file contains instructions, data and text sections, labels and comments but with errors

.data	//this is data section
num: .word 123	#this is single integer
array : .word 1, 2, 3, abcd	// this is an array of integers
string : .ascii "xyz"	#this is string
string2 : 
string3: .abc 12
array1: .space 32	this allocates space for label array1
add: .word 3 

.text
main:
la $t0, number
lw $t1, 0($t0)
lb $t2, abcd($t0)
sw $t1, 0($t0)
sb $t2, 0($t0)
number : .word 123

L1:
add $t2, $t0, $d5
addu $t2,$t0,100
sub $t2, $t0, array
subu $t2,$t0,$t1
slt $t3, $t0, $t1
sltu $t3, $t0, $t1

L2:
and $s0, $t0, $t1
or $s0, $t0, $t1
xor $s0, $t0, $t1
nor $s0, $t0, $t1
sll $s1,$t0,$t3
srl $s1,$t0,50
sra $s1,$t0,number

L3:
mult $s0,$t2, $t3
multu $s0
div $s0,$t2
mfhi $s7,$t5
divu $s0,$t2
mflo $t5
addi $t0,$t1,-1
addiu $t0,$t1,1

L4:
andi $t0, $t2, $t5
ori $t0,
xori $t0, $t2, 2
lui $s3, 12345678900987654321
slti $s8, $s4, -100
beq $s7,$s6,L23
bne $s7, $s8, L1
blez $t5, L2
bgtz $t6, L2
bltz $t5, L3
bgez $t6, L3
nop	$12
sltiu $t8, $t3, 100
li $t3,6789xyz
li $t5, -12345
move $s2, $s4, $s3
j $s2
jal L2
jalr $ra
jr L1

exit:
li $v0,10
syscall