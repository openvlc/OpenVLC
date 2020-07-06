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

	.cdecls "main_pru0.c"


	.clink
	.global START0

START0: ; 5 Instructions - 1 not done before

 ; Enable the OCP master port -- allows transfer of data to Linux userspace
	LBCO    &r0, C4, 4, 4     ; load SYSCFG reg into r0 (use c4 const addr)
	CLR     r0, r0, 4        ; clear bit 4 (STANDBY_INIT)
	SBCO    &r0, C4, 4, 4     ; store the modified r0 back at the load addr
	
	CLR r30, r30.t0
	LDI32 r5, 0x00000FFF ; Mask
	LDI32 r6, 0x00010000 ; Address memory where PRU1 store the address of new sample
	LDI32 r4, 0x00011FFF ; Address limit

RESTART:
	LDI32 r1, 0x00010004
	
;;;;;;;;;;;;;;; RX Code ;;;;;;;;;;;;;;;	
GET_SAMPLE:	
	LDI32 r7, 7 ; x - 110 instructions (55)
 	CLR r30, r30.t0 ; set the CS line low (active low)
	SET r30, r30.t3
	QBBC ZERO1, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX1
ZERO1:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX1
CONT_RX1:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30, r30.t3
	QBBC ZERO2, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX2
ZERO2:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX2
CONT_RX2:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30, r30.t3
	QBBC ZERO3, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX3
ZERO3:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX3
CONT_RX3:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30, r30.t3
	QBBC ZERO4, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX4
ZERO4:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX4
CONT_RX4:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO5, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX5
ZERO5:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX5
CONT_RX5:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO6, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX6
ZERO6:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX6
CONT_RX6:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO7, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX7
ZERO7:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX7
CONT_RX7:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO8, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX8
ZERO8:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX8
CONT_RX8:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO9, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX9
ZERO9:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX9
CONT_RX9:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO10, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX10
ZERO10:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX10
CONT_RX10:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO11, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX11
ZERO11:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX11
CONT_RX11:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO12, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX12
ZERO12:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX12
CONT_RX12:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO13, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX13
ZERO13:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX13
CONT_RX13:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO14, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX14
ZERO14:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX14
CONT_RX14:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO15, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX15
ZERO15:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX15
CONT_RX15:
	CLR r30, r30.t3
	LSL r3, r3, 1
	SET r30,  r30.t3
	QBBC ZERO16, r31, 2
	OR r3, r3, 0x00000001
	;JMP CONT_RX16
ZERO16:
	;OR r3, r3, 0x00000000
	;JMP CONT_RX16
CONT_RX16:
	CLR r30, r30.t3
	
	
	
	SET r30,  r30.t0 	; pull the CS line high (end of sample)
	LSR r3, r3, 2       ; SPICLK shifts left too many times left, shift right once
	AND r3, r3, r5 		; AND the data with mask to give only the 10 LSBs
	
	; Save the data in the shared memory
	SBBO &r3, r1, 0, 4
	SBBO &r1, r6, 0, 4
	ADD r1, r1, 4
	
	;sub r7, r7, 55

	
NOT_RESTART:	
; Received 72 = 144 instructions (each 1 received add 2 instructions so 80 (160 instructions))
	;ADD r7, r7, 11
;WAIT: ; 3 (not taking into account wait)
	;SUB r7, r7, 1
	;QBNE WAIT, r7, 0	
	
	QBGE RESTART, r4, r1
	JMP GET_SAMPLE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/	

	HALT
