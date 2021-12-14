# @file linkedList.asm
# @author Maíra Canal (@mairacanal)\
# A simple Singly Linked List in MIPS

.data
	vetor:	.word 15, 31, 63, 127, 255, 511, 1023, 2047, 4067, 65536, 0
	head:	.space 4
	space: 	.asciiz " "
.text
.globl main

main:
	la $s0, vetor			# load vetor address
	
	lw $a0, 0($s0)			# load first word from vetor
	la $a1, head			# load linked list head
	jal addNode			# add first node
	move $a1, $v0			# save the address of the next pointer	
	
	addAllNodes:
		addi $s0, $s0, 4
		
		lw $a0, 0($s0)						
		jal addNode
		move $a1, $v0
		
		bnez $a0, addAllNodes
		
	jal printList
	
	li $v0, 10			# syscall to finish execution 
	syscall	
	
# Add node to linked list
# $a0: element in node
# $a1: address of next pointer of previous node
# $v0: address of next pointer
addNode:
	sub $sp, $sp, 8			# push $ra and $a0 to the stack
	sw $a0, 4($sp)
	sw $ra, 0($sp)
	
	jal allocateSpace		# allocate space for the node
	move $t0, $v0			# move the address of the allocated memory to a register
	
	lw $a0, 4($sp)			# pop $ra and $a0 of the stack
	lw $ra, 0($sp)
	addi $sp, $sp, 8
	
	sw $a0, 0($t0)			# store integer in the node
	sw $zero, 4($t0)		# store NULL in next field of current node	
	
	sw $t0, 0($a1)			# store the address of the current node on the next pointer of the previous node
	
	move $v0, $t0			# store the address of next pointer of the current node 
	addi $v0, $v0, 4		
	
	jr $ra

# Allocate space for a node
# $v0: contains address of allocated memory
allocateSpace:
	li $v0, 9			# syscall to allocate space
	li $a0, 8			# allocates 8 bytes (4 for the integer and 4 for next pointer)
	syscall
	
	jr $ra
	
# Print the linked list
printList:
	la $t0, head			# load address of the head pointer of the list
	lw $t1, 0($t0)			# $t1 = address of the first node
	
	loop:
		lw $t2, 0($t1)		# $t2 = element of the node
		lw $t3, 4($t1)		# $t3 = next pointer of the node
	
		beqz $t3, exit
		
		la $v0, 1		# syscall to print integer
		move $a0, $t2
		syscall
		
		la $v0, 4		# syscall to print string 
		la $a0, space
		syscall
		
		move $t1, $t3		# $t1 = address of the next node
		
		j loop
		
	exit:		
		jr $ra		
