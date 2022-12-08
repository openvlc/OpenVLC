;*
;* Copyright (C) 2016 Zubeen Tolani <ZeekHuge - zeekhuge@gmail.com>
;* IMDEA NETWORKS Institute: This file has been modified and it is part of the OpenVLC's source codes
;* This file is as an example to show how to develope
;* and compile inline assembly code for PRUs
;*
;* This program is free software; you can redistribute it and/or modify
;* it under the terms of the GNU General Public License version 2 as
;* published by the Free Software Foundation.
;* define PRU0_R31_VEC_VALID 32    
 .asg 32, PRU0_R31_VEC_VALID ;* allows notification of program completion
 ;*#define PRU_EVTOUT_0    3 
 .asg 3, PRU_EVTOUT_0 ;* the event number that is sent back
       
	.cdecls "main_pru1.c"
	.clink
	.global START

START: ;*;* 5 Instructions - 1 not done before

 ;* Enable the OCP master port -- allows transfer of data to Linux userspace
	LBCO    &r0, C4, 4, 4     ;* load SYSCFG reg into r0 (use c4 const addr)
	CLR     r0, r0, 4        ;* clear bit 4 (STANDBY_INIT)
	SBCO    &r0, C4, 4, 4     ;* store the modified r0 back at the load addr
	
	CLR r30, r30.t0
	LDI32 r10, 0x00000000 ;* 32-bit value read from memory to send	
	LDI32 r11, 0x00000000 ;* Read memory pointer
	LDI32 r15, 32 ;* bit counter inside a 32-bit value
	LDI32 r16, 0x00000000 ;* frame flag value and counter of positions left to be read
	LDI32 r17, 0x00000000 ;* pointer to flag frame address
	LDI32 r5, 0x00000FFF ;* Mask
	LDI32 r6, 0 ;* Zero pointer
	LDI32 r7, 100 ;* x - 110 instructions (55)
	LDI32 r8, 24
	LDI32 r9, 69; duty cycle

;* This procedure applies an SPI clock cycle to the SPI clock and on the rising edge of the clock
;* it writes the current MSB bit in r2 (i.e. r31) to the MOSI pin. On the falling edge, it reads
;* the input from MISO and stores it in the LSB of r3. 
;* The clock cycle is determined by the datasheet of the product where TIME_CLOCK is the
;* time that the clock must remain low and the time it must remain high (assuming 50% duty cycle)
;* The input and output data is shifted left on each clock cycle
	
;*;*;*;*;*;*;*;*;*;*;*;*;*;*;* TX Code ;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*
TX_SAMPLE:  
	LDI32 r7, 100 ;* TX Frequency
	QBNE CONT_TX, r16, 0
	LDI32 r11, 0x00000000
	CLR r30, r30.t0
	CLR r30, r30.t1
	LBBO &r16, r17, 0, 4
	QBEQ TX_SAMPLE, r16, 0
	CLR r30, r30.t1
	SUB r7, r7, 3  ;* Compensate all this instructions
CONT_TX:
	QBNE NEW_BIT, r15, 32
	LDI32 r15, 0x00000000
	ADD r11, r11, 4
	LBBO &r10,r11, 0, 4
	LDI32 r6, 0
	SUB r7, r7, 3 ;* Compensate all this instructions
NEW_BIT:
	SUB r7, r7, 2 ;* Compensate line 48, 54 and 62
	QBBC TX_LOW, r10, 31
TX_HIGH: 
	SET r30, r30.t0
	CLR r30, r30.t1
WAIT_75:
	SUB r8, r8, 1
	QBNE WAIT_75, r8, 0	
CONT_TX_HIGH:
	SET r30, r30.t1
	CLR r30, r30.t0
WAIT_25:
	SUB r9, r9, 1
	QBNE WAIT_25, r9, 0	
	;CLR r30, r30.t1
	LDI32 r8, 24
	LDI32 r9, 69
CONT_ONE:
	LSL r10,r10, 1
	ADD r15, r15, 1
	LDI32 r6, 0
	SUB r16, r16, 1
	CLR r30, r30.t1
	QBNE TX_SAMPLE, r16, 0
	SBBO &r6, r17, 0, 4
	LDI32 r15, 32
	JMP TX_SAMPLE
TX_LOW:
	CLR r30, r30.t0
	JMP CONT_ZERO
CONT_ZERO:
	LSL r10,r10, 1
	ADD r15, r15, 1
	SUB r7, r7, 4 ;* Compensate all this instructions
	LDI32 r6, 0
	SUB r16, r16, 1
	QBNE WAIT, r16, 0
	SBBO &r6, r17, 0, 4
	LDI32 r15, 32
	SUB r7, r7, 2

;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*/	
	

;* Received 72 = 144 instructions (each 1 received add 2 instructions so 80 (160 instructions))
	
WAIT: ;* 3 (not taking into account wait)
	SUB r7, r7, 1
	QBNE WAIT, r7, 0	
	JMP TX_SAMPLE

;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*;*/		

	HALT
