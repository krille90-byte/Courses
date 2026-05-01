# Lampor
.eqv NO_LIGHT 0x00 # lampa av
.eqv RED_LIGHT 0x01 # röd lampa för alla
.eqv WALK_LIGHT 0x02 # grön lampa för gående individer.
.eqv YELLOW_LIGHT 0x02 # gul lampa för bilister
.eqv RED_YELLOW_LIGHT 0x03 # Röd och gul för bilister
.eqv GREEN_LIGHT 0x04 # grön lampa för bilister
.eqv PEDESTRIAN_LIGHT_ADR 0xFFFF0010 # Adressen för "gående invdivid" lamporna.
.eqv CAR_LIGHT_ADR 0xFFFF0011 # Adressen för billamporna

# Timer och masksar
.eqv EXT_BUTTON 0x0800 # mask for timer interrupts (external), bit 10
.eqv EXT_INTTIME 0x0400 # mask for timer interrupts (external), bit 10
.eqv CLEAR_TIME 0xFFFFFBFF # mask for clearing timer interrupts, bit 10
.eqv CLEAR_STATUS 0xFFFFF3FF
.eqv EXCHMASK 0x007c # mask for excpetions (internal), bits 2-6
.eqv ENABLE_TIMER_ADR 0xFFFF0012 # I/O enabling timer
.eqv ENABLE_TIMER 0x01 # mask for enabling timer

# Knapparna
.eqv BUTTON_ADR 0xFFFF0013 # I/O button address
.eqv WALK_BUTTON 0x01 # Övergångstället
.eqv CAR_SENSOR 0x02 # bilsensor

.data
	timer: .word 0
	utsaga: .word 0 # 0 = default utsaga(värde), bil grön; 1 = ga_hantering, "exekverar"; 2 = knapptryck men ej grönt länge nog än, avvaktar.
	
	.ktext 0x80000180
	la $k0, avbrotts_hanteringen
	jr $k0
	nop
.text

main:
	mfc0 $t0, $12 # Förbereder status registret för timer avbrott
	ori $t0, $t0, EXT_INTTIME
	ori $t0, $t0, EXT_BUTTON
	ori $t0, $t0, 1
	mtc0 $t0, $12
	
	# initialiserar trafikljusen
	li $t0, RED_LIGHT
	sb $t0, PEDESTRIAN_LIGHT_ADR
	li $t0, GREEN_LIGHT
	sb $t0, CAR_LIGHT_ADR
	
	
	li $t0, ENABLE_TIMER # kopplar in vår timer (t0 > 0)
	sb $t0, ENABLE_TIMER_ADR
		
		loop:
		nop
		b loop
	
		li $v0, 10
		syscall
	
		avbrotts_hanteringen:
		mfc0 $k1, $13 # Försöker att inte ändra k1 mer, om det är möjligt såklart.
		andi $k0, $k1, EXCHMASK
		bne $k0, $zero, restore
		andi $k0, $k1, EXT_INTTIME
		bne $k0, $zero, tids_hanteringen
		andi $k0, $k1, EXT_BUTTON
		bne $k0, $zero, knapp_hanteringen
		b restore
	
		tids_hanteringen:	# Timer hanteringen.
		# Ökar timern med 1
		lw $k0, timer
		addi $k0, $k0, 1
		sw $k0, timer
	
		# om utsagan är 2 och timern exakt 10
		lw $k0, utsaga
		beq $k0, 2, utsaga2
		
		b ga_vidare
		
		utsaga2:
		lw $k0, timer
		bne, $k0, 10, restore
		
		b honk_honk_driving # Kör som om att knappen tryckts
		
		ga_vidare:
	
		lw $k0, utsaga
		bne $k0, 1, utsaga1ifend
		
		lw $k0, timer
		bne $k0, 3, utsaga1_ga_vidare3 # Om timer är 3, Ändra bil till röd, fotgängare till grön
		
		li $k0, RED_LIGHT
		sb $k0, CAR_LIGHT_ADR
			
		li $k0, WALK_LIGHT
		sb $k0, PEDESTRIAN_LIGHT_ADR
			
		b utsaga1ifend # Behöver inte kolla mer, hoppar till slutet. Inte nödvändigt men snabbar säkert upp.
		
		utsaga1_ga_vidare3:
		lw $k0, timer
		bne $k0, 10, utsaga1_ga_vidare10 # Timer 10: Släck fotgäng.
		
		li $k0, NO_LIGHT
		sb $k0, PEDESTRIAN_LIGHT_ADR
			
		b utsaga1ifend # --||--
		
		utsaga1_ga_vidare10:
		lw $k0, timer
		bne $k0, 11, utsaga1_ga_vidare11 # Timer 11: Tänd röd lampa för fotgäng.
		
		li $k0, RED_LIGHT
		sb $k0, PEDESTRIAN_LIGHT_ADR
			
		b utsaga1ifend # --||--
		
		utsaga1_ga_vidare11:
		lw $k0, timer
		bne $k0, 12, utsaga1_ga_vidare12 # Timer 12: Släck fotgäng.
			
		li $k0, NO_LIGHT
		sb $k0, PEDESTRIAN_LIGHT_ADR
			
		b utsaga1ifend # --||--
		
		utsaga1_ga_vidare12:
		lw $k0, timer
		bne $k0, 13, utsaga1_ga_vidare13 # Timer 13: Tänd röd fotgäng. för gul för bil
			
		li $k0, RED_LIGHT
		sb $k0, PEDESTRIAN_LIGHT_ADR
			
		li $k0, RED_YELLOW_LIGHT
		sb $k0, CAR_LIGHT_ADR
			
		b utsaga1ifend # --||--
		
		utsaga1_ga_vidare13:
		lw $k0, timer
		bne $k0, 16, utsaga1_ga_vidare16 # Timer 16: Grönt för bil.
			
		li $k0, GREEN_LIGHT
		sb $k0, CAR_LIGHT_ADR
			
		# Återställer timern och utsagan
		sw $zero, timer
		sw $zero, utsaga
			
		b utsaga1ifend # --||--
		
		utsaga1_ga_vidare16:
		utsaga1ifend:
	
		b restore
	
		knapp_hanteringen:
		lb $k0, BUTTON_ADR
		andi $k0, $k0, WALK_BUTTON
		bne $k0, $zero, ga_hantering
	
		b restore
	
		ga_hantering: # knapptryck på övergångstället
		lw $k0, utsaga
		beq, $k0, 1, restore
		lw $k0, timer
		bge $k0, 10, honk_honk_driving # Om utsagan inte är 1 (redan i trafikljus-cykeln) och timer är mer än 10, kör direkt.
		
		li $k0, 2
		sw $k0, utsaga # annars sätter vi utsaga till 2 och avvaktar att timern blir 10
		b restore
	
		honk_honk_driving:
		sw $zero, timer # Återställer timern
	
		# sätt utsaga till 1
		li $k0, 1
		sw $k0, utsaga
	
		li $k0, YELLOW_LIGHT
		sb $k0, CAR_LIGHT_ADR
	
		b restore
	
		restore:
		mtc0 $zero, $13 # lägg 0 i cause-registret.
		eret
