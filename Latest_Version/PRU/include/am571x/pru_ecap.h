/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PRU_ECAP_H_
#define _PRU_ECAP_H_

/* PRU ECAP register set */
typedef struct {

	/* PRU_ECAP_TSCNT register bit field */
	union {
		volatile uint32_t TSCNT;

		volatile struct {
			uint32_t TSCNT : 32; // 31:0
		} TSCNT_bit;
	}; // 0x0

	/* PRU_ECAP_CNTPHS register bit field */
	union {
		volatile uint32_t CNTPHS;

		volatile struct {
			uint32_t CNTPHS : 32; // 31:0
		} CNTPHS_bit;
	}; // 0x4

	/* PRU_ECAP_CAP1 register bit field */
	union {
		volatile uint32_t CAP1;

		volatile struct {
			uint32_t CAP1 : 32; // 31:0
		} CAP1_bit;
	}; // 0x8

	/* PRU_ECAP_CAP2 register bit field */
	union {
		volatile uint32_t CAP2;

		volatile struct {
			uint32_t CAP2 : 32; // 31:0
		} CAP2_bit;
	}; // 0xc

	/* PRU_ECAP_CAP3 register bit field */
	union {
		volatile uint32_t CAP3;

		volatile struct {
			uint32_t CAP3 : 32; // 31:0
		} CAP3_bit;
	}; // 0x10

	/* PRU_ECAP_CAP4 register bit field */
	union {
		volatile uint32_t CAP4;

		volatile struct {
			uint32_t CAP4 : 32; // 31:0
		} CAP4_bit;
	}; // 0x14

	uint8_t rsvd18[16]; // 0x18 - 0x27

	/* PRU_ECAP_ECCTL1 register bit field */
	volatile uint16_t ECCTL1; // 0x28

	/* PRU_ECAP_ECCTL2 register bit field */
	volatile uint16_t ECCTL2; // 0x2a

	/* PRU_ECAP_ECEINT register bit field */
	volatile uint16_t ECEINT; // 0x2c

	/* PRU_ECAP_ECFLG register bit field */
	volatile uint16_t ECFLG; // 0x2e

	/* PRU_ECAP_ECCLR register bit field */
	volatile uint16_t ECCLR; // 0x30

	uint8_t rsvd32[2]; // 0x32 - 0x33

	/* PRU_ECAP_ECFRC register bit field */
	volatile uint16_t ECFRC; // 0x34

	uint8_t rsvd36[38]; // 0x36 - 0x5b

	/* PRU_ECAP_PID register bit field */
	union {
		volatile uint32_t PID;

		volatile struct {
			uint32_t REVISION : 32; // 31:0
		} PID_bit;
	}; // 0x5c

} pruEcap;

volatile __far pruEcap CT_ECAP __attribute__((cregister("PRU_ECAP", near), peripheral));

#endif /* _PRU_ECAP_H_ */

