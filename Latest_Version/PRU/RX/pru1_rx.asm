;* IMDEA NETWORKS Institute: This file has been modified and it is part of the OpenVLC's source codes
 .asg 32, PRU0_R31_VEC_VALID ;* allows notification of program completion
 ;*#define PRU_EVTOUT_0    3 
 .asg 3, PRU_EVTOUT_0 ;* the event number that is sent back

	.cdecls "main_pru1.c"


	.clink
	.global START1
	
START1:

RESTART:
	
        ; Enable the OCP master port -- allows transfer of data to Linux userspace
	LBCO    &r0, C4, 4, 4   ; load SYSCFG reg into r0 (use c4 const addr)
	CLR     r0, r0, 4       ; clear bit 4 (STANDBY_INIT)
	SBCO    &r0, C4, 4, 4   ; store the modified r0 back at the load addr
	LDI32 r1, 0x00002000 	; load the base address into r1
	LDI32 r2, 0x00000000 	; Sample
	LDI32 r3, 0x00010004 	; Memory of new sample
	LDI32 r4, 0x00010000 	; Address of shared memory flag
	LDI32 r5, 0x00000000 	; Number of equal samples
	LDI32 r6, 0x000000FF 	; Mask
	LDI32 r7, 0x00000000	; Symbols to add (LSB)
	LDI32 r8, 0x00000000 	; Last sample (decoded)
	LDI32 r9, 0x00000000 	; Actual sample (decoded)
	LDI32 r10, 0x00000000
	
	LDI32 r12, 0x00000000	; 32 - symbols group
	LDI32 r13, 0x00000000	; Symbols in last register
	LDI32 r14, 32 			; Number of bits per memory address
	LDI32 r15, 0xAAAAAAAA	; Preamble
	LDI32 r16, 0x00000000 	; Temporary pointer register
	LDI32 r17, 0x00000000	; Reg storing samples counter
	LDI32 r18, 1021		; Threshold 803 (75kohm)
	LDI32 r19, 0x00000000 	; Manchester decoded bit
	LDI32 r20, 0x00000000	;Current symbol
	SBBO &r20, r1, 0, 4
	LDI32 r21, 0x00000000	;Next symbol
	LDI32 r24, 0x00000000	; Symbols for the length
	LDI32 r25, 0x00000000	;Preamble
	LDI32 r26, 0x00000000 	; Length
	LDI32 r27, 0x000000A3 	; SFD
	LDI32 r28, 0x00000000 	; bit 0 flag for bit slip
	LDI32 r29, 0x00000000 	; Zero register
	clr r30, r30.t12

;;;;;;;;; GET PREAMBLE ;;;;;;;;;
; GET_PREAMBLE: 
	
	; JAL r11.w0, GET_SAMPLE
	; LSL r25, r25, 1
	; QBBC PREAMBLE_ZERO, r8, 0
	; SET r25, r25.t0
; PREAMBLE_ZERO:	
	; QBEQ PREAMBLE_DETECTED, r25, r15
	; JMP GET_PREAMBLE
PREAMBLE_DETECTED:
;;;;;;;;; GET SFD ;;;;;;;;;
	set r30, r30.t10
	JAL r11.w0, GET_SAMPLE
	QBBC NO_NEW_BIT1, r28, 0
	
	LSL r25, r25, 1
	ADD r25, r25, r10
	CLR r28, r28.t0
	AND r25, r25, r6
NO_NEW_BIT1:	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;
	QBEQ SFD_DETECTED, r25, r27
	JMP PREAMBLE_DETECTED
SFD_DETECTED:
	clr r30, r30.t10
;;;;;;;;; GET LENGTH ;;;;;;;;;
GET_LENGTH:	
	JAL r11.w0, GET_SAMPLE
	QBBC NO_NEW_BIT2, r28, 0
	ADD r24, r24, 1
	LSL r26, r26, 1
	ADD r26, r26, r10
	CLR r28, r28.t0
NO_NEW_BIT2:
	QBEQ LENGTH_OBTAINED, r24, 16
	JMP GET_LENGTH
LENGTH_OBTAINED:
	
;;;;;;;;; STORE DATA ;;;;;;;;;
	set r30, r30.t12
	LDI32 r1, 0x00002004
	QBGT RESTART, r26, 200
	LDI32 r17, 32000
	QBLT RESTART, r26, r17
	SBBO &r26, r1, 0, 4
	
	
	
	SUB r26, r26, 81 ; this must be change with the tx
	LSR r26, r26, 1
	LDI32 r17, 0x00000000
	ADD r1, r1, 4
	
	set r30, r30.t9
	
STORE_DATA:
	
	JAL r11.w0, GET_SAMPLE
	QBBC NO_NEW_BIT3, r28, 0
	CLR r28, r28.t0
	SUB r26, r26, 1
	LSL r12, r12, 1
	ADD r12, r12, r10
	ADD r17, r17, 1
NO_NEW_BIT3:	
	QBNE STORE_DATA, r17, 32
	
	LDI32 r17, 0x00000000
	SBBO &r12.b3, r1, 0, 4 ; store the value r2 in memory
	SBBO &r12.b2, r1, 1, 4 ; store the value r2 in memory
	SBBO &r12.b1, r1, 2, 4 ; store the value r2 in memory
	SBBO &r12.b0, r1, 3, 4 ; store the value r2 in memory
	LDI32 r12, 0x00000000
	ADD r1, r1, 4
	
	QBLE LAST_REG, r14, r26
	
	JMP STORE_DATA
	
LAST_REG:
	SUB r13, r14, r26
LAST_BITS:
	JAL r11.w0, GET_SAMPLE
	QBBC NO_NEW_BIT4, r28, 0
	CLR r28, r28.t0
	SUB r26, r26, 1
	LSL r12, r12, 1
	ADD r12, r12, r10
NO_NEW_BIT4:	
	QBNE LAST_BITS, r26, 0
	LSL r12, r12, r13
	SBBO &r12.b3, r1, 0, 4 ; store the value r2 in memory
	SBBO &r12.b2, r1, 1, 4 ; store the value r2 in memory
	SBBO &r12.b1, r1, 2, 4 ; store the value r2 in memory
	SBBO &r12.b0, r1, 3, 4 ; store the value r2 in memory
	LDI32 r12, 0x00000000
	LDI32 r1, 0x00002000
	LDI32 r20, 1
	SBBO &r20, r1, 0,4
WAIT_FOR_US_TO_READ:
	LBBO &r20,r1, 0, 4
	QBNE WAIT_FOR_US_TO_READ,r20,0
	clr r30, r30.t9
	JMP RESTART

GET_SAMPLE:
	;; Get a sample ;;
	LBBO &r3, r4, 0,4 		; Load memory of new sample
	QBEQ GET_SAMPLE, r3, 0	; Check if there is new sample to be read
	LBBO &r2, r3, 0, 4		; Load the sample
	SBBO &r29, r4, 0, 4		; Clean the flag
	
	;; Decode the sample
	QBLT SAMPLE_ZERO, r18, r2
	LDI32 r9, 0x00000001
	
	JMP CONT
SAMPLE_ZERO:	
	LDI32 r9, 0x00000000
CONT:



;; Decode the samples 
	QBEQ EQUAL, r8, r9
	
	QBBS FLAG_ACTIVE, r28, 1
	MOV r10, r9					;; Pass the actual value (Man decoded)
	SET r28, r28.t0				;; Set the flag	
	SET r28, r28.t1				;; Set the flag	
	LDI32 r7, 0x00000001 		;; Reset the counter
	MOV r8, r9					;; Shift data register
	JMP r11.w0

FLAG_ACTIVE:
	QBGE NO_NEW_SYMBOL, r7, 3
	MOV r10, r9					;; Pass the actual value (Man decoded)
	SET r28, r28.t0				;; Set the flag
	LDI32 r7, 0x00000001 		;; Reset the counter
	MOV r8, r9					;; Shift data register	
	JMP r11.w0				
	
NO_NEW_SYMBOL:
	CLR r28, r28.t1				;; Reset the flag	
	LDI32 r7, 0x00000001 		;; Reset the counter
	MOV r8, r9					;; Shift data register
	JMP r11.w0
	
	
EQUAL:
	ADD r7, r7, 1
	MOV r8, r9	
	JMP r11.w0
	
	
	
