.data
	vek: .word 4, 5, 2, 2, 1, 6, 7, 9, 5, 10
	antal: .word 10
	
	nyRad: .asciiz "\n"
	mlnRum: .asciiz " "
.text

.globl main
main:
	# skriv(vek, antal);
	la $a0, vek
	lw $a1, antal
	add $sp, $sp, -16
	jal skriv
	add $sp, $sp, 16

	# quickSort(vek, 0, antal-1);
	lw $a1, antal
	add $a2, $a1, -1
	li $a1, 0
	la $a0, vek
	add $sp, $sp, -16
	jal quickSort
	add $sp, $sp, 16

	# skriv(vek, antal)
	la $a0, vek
	lw $a1, antal
	add $sp, $sp, -16
	jal skriv
	add $sp, $sp, 16

	# Avslutar programmet
	li $v0, 10
	syscall

.globl partition
partition:
	sll $t5, $a1, 2
	add $a0, $a0, $t5
	lw $t0, ($a0) # pivot = v[a]
	sub $a0, $a0, $t5
	addi $t1, $a1, 1 # lower = a + 1
	move $t2, $a2 # upper = b
	
	do_while:
		#Dubbla while loopar
		while_lowerside:
			sll $t6, $t1, 2 # uppdaterar offset med lower
			add $a0, $a0, $t6
			lw $t3, ($a0)
			sub $a0, $a0, $t6
			bgt $t3, $t0, while_lowerside_end
			bgt $t1, $t2, while_lowerside_end
			
			addi $t1, $t1, 1
			j while_lowerside
		while_lowerside_end:
		
		while_upper:
			sll $t7, $t2, 2 # uppdaterar offset med upper
			add $a0, $a0, $t7
			lw $t3, ($a0)
			sub $a0, $a0, $t7
			ble $t3, $t0, while_upper_end
			bgt $t1, $t2, while_upper_end
			
			addi $t2, $t2, -1
			j while_upper
		while_upper_end:
		
		bgt $t1, $t2, if_end
			add $a0, $a0, $t6
			lw $t3, ($a0) # temp  = v[lower]
			sub $a0, $a0, $t6
			
			add $a0, $a0, $t7
			lw $t4, ($a0) # egen temp = v[upper]
			sub $a0, $a0, $t7
			
			add $a0, $a0, $t6
			sw $t4, ($a0) # v[lower] = v[upper]
			sub $a0, $a0, $t6
						
			add $a0, $a0, $t7 # Offsetar med upper
			sw $t3, ($a0)
			sub $a0, $a0, $t7
			
			addi $t1, $t1, 1
			addi $t2, $t2, -1
		if_end:
		bgt $t2, $t1, do_while
	do_while_end:
	sll $t7, $t2, 2 # uppdaterar offset med upper
	add $a0, $a0, $t7
	lw $t3, ($a0)
	sub $a0, $a0, $t7
	
	add $a0, $a0, $t5
	lw $t8, ($a0)
	sub $a0, $a0, $t5
	
	add $a0, $a0, $t7
	sw $t8, ($a0)
	sub $a0, $a0, $t7
	
	add $a0, $a0, $t5
	sw $t3, ($a0)
	sub $a0, $a0, $t5
	
	move $v0, $t2
	jr $ra

.globl quickSort
quickSort:
	# Flyttar stackpeckaren
	add $sp, $sp, -16
	sw $ra, 12($sp) # Sparar returadressen
	# Sparar argumenten
	sw $a1, 0($sp) 
	sw $a2, 4($sp)

	# if (a < b)
	blt $a1, $a2, L1
	b endif
	L1:
		# Förbereder argumenten från subrutinerna
		add $sp, $sp, -16
		jal partition
		add $sp, $sp, 16
		add $a2, $v0, -1
		sw $v0, 8($sp)
		add $sp, $sp, -16
		jal quickSort
		add $sp, $sp, 16
		lw $v0, 8($sp)
		add $a1, $v0, 1
		lw $a2, 4($sp)
		add $sp, $sp, -16
		jal quickSort
		add $sp, $sp, 16
	endif:
	lw $ra, 12($sp) # Hämtar rätt returvärde
	add $sp, $sp, 16 # Återställer stackpekaren
	jr $ra

.globl skriv
skriv:
	# Flyttar stackpeckaren
	add $sp, $sp, -8
	sw $a0, 0($sp) # Sparar undan a0

	# Skriva ut ny rad
	li $v0, 4
	la $a0, nyRad
	syscall

	# For loop
	li $t0, 0 # i
	lw $t1, 0($sp) # a0 (arrayen)
	for:
		bge $t0, $a1, end
		li $v0, 1 # Skriva ut int
		lw $t2, ($t1) # Hämtar värdet på adressen till $t2
		add $a0, $t2, $zero # Hämtar v[i]
		syscall
	
		# Mellanrum
		li $v0, 4
		la $a0, mlnRum
		syscall
		# Mellanrum
	
		addi $t1, $t1, 4 # Offsetar pekaren 4 (storleken av ett ord)
		addi $t0, $t0, 1 # i++
		j for
	end:

	# Skriver ut en ny rad
	li $v0, 4
	la $a0, nyRad
	syscall

	add $sp, $sp, 8 # Återställer stackpekaren
	jr $ra
