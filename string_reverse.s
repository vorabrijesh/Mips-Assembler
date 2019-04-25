.data
string: .ascii "iit tirupati" #'i', 'i', 't', 't', 'i', 'r', 'u', 'p', 'a', 't', 'i'
newline: .ascii "\n"

.text
swap:
add $t2,$a0,$a1
add $t3,$a0,$a2
lb $t0,0($t2)
lb $t1,0($t3)
sb $t0,0($t3)
sb $t1,0($t2)
jr $ra

main:
la $s0,string
li $s1,12	#stringsize
srl $s2,$s1,1	#size/2
add $s3,$0,$0	#loop counter

print:
add $t0,$s1,$0	#size
add $t1,$s0,$0	#array base address
loop:
beq $t0,$0,L1
addi $t0,$t0,-1
li $v0,11
lb $a0,0($t1)
syscall
addi $t1,$t1,1
j loop

L1:
la $a0,newline
li $v0,4
syscall
add $a0,$s0,$0	#string base address
add $a1,$0,$0	#i
addi $a2,$s1,-1	#size-i-1

reverse:
beq $s3,$s2,exit
jal swap
addi $a1,$a1,1
addi $a2,$a2,-1
addi $s3,$s3,1
j reverse

exit:
print1:
add $t0,$s1,$0	#size
add $t1,$s0,$0	#array base address
loop1:
beq $t0,$0,L2
addi $t0,$t0,-1
li $v0,11
lb $a0,0($t1)
syscall
addi $t1,$t1,1
j loop1

L2:
li $v0,10
syscall
