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

#ifndef _PRU_IEP_H_
#define _PRU_IEP_H_

/* PRU IEP register set */
typedef struct {

	/* PRU_IEP_TMR_GLB_CFG register bit field */
	union {
		volatile uint32_t TMR_GLB_CFG;

		volatile struct {
			uint32_t CNT_ENABLE : 1; // 0
			uint32_t rsvd1 : 3; // 3:1
			uint32_t DEFAULT_INC : 4; // 7:4
			uint32_t CMP_INC : 12; // 19:8
			uint32_t rsvd20 : 12; // 31:20
		} TMR_GLB_CFG_bit;
	}; // 0x0

	/* PRU_IEP_TMR_GLB_STS register bit field */
	union {
		volatile uint32_t TMR_GLB_STS;

		volatile struct {
			uint32_t CNT_OVF : 1; // 0
			uint32_t rsvd1 : 31; // 31:1
		} TMR_GLB_STS_bit;
	}; // 0x4

	/* PRU_IEP_TMR_COMPEN register bit field */
	union {
		volatile uint32_t TMR_COMPEN;

		volatile struct {
			uint32_t COMPEN_CNT : 24; // 23:0
			uint32_t rsvd24 : 8; // 31:24
		} TMR_COMPEN_bit;
	}; // 0x8

	/* PRU_IEP_TMR_CNT register bit field */
	union {
		volatile uint32_t TMR_CNT;

		volatile struct {
			uint32_t COUNT : 32; // 31:0
		} TMR_CNT_bit;
	}; // 0xc

	uint8_t rsvd10[48]; // 0x10 - 0x3f

	/* PRU_IEP_TMR_CMP_CFG register bit field */
	union {
		volatile uint32_t TMR_CMP_CFG;

		volatile struct {
			uint32_t CMP0_RST_CNT_EN : 1; // 0
			uint32_t CMP_EN : 8; // 8:1
			uint32_t rsvd9 : 23; // 31:9
		} TMR_CMP_CFG_bit;
	}; // 0x40

	/* PRU_IEP_TMR_CMP_STS register bit field */
	union {
		volatile uint32_t TMR_CMP_STS;

		volatile struct {
			uint32_t CMP_HIT : 8; // 7:0
			uint32_t rsvd8 : 24; // 31:8
		} TMR_CMP_STS_bit;
	}; // 0x44

	/* PRU_IEP_TMR_CMP0 register bit field */
	union {
		volatile uint32_t TMR_CMP0;

		volatile struct {
			uint32_t CMP0 : 32; // 31:0
		} TMR_CMP0_bit;
	}; // 0x48

	/* PRU_IEP_TMR_CMP1 register bit field */
	union {
		volatile uint32_t TMR_CMP1;

		volatile struct {
			uint32_t CMP1 : 32; // 31:0
		} TMR_CMP1_bit;
	}; // 0x4c

	/* PRU_IEP_TMR_CMP2 register bit field */
	union {
		volatile uint32_t TMR_CMP2;

		volatile struct {
			uint32_t CMP2 : 32; // 31:0
		} TMR_CMP2_bit;
	}; // 0x50

	/* PRU_IEP_TMR_CMP3 register bit field */
	union {
		volatile uint32_t TMR_CMP3;

		volatile struct {
			uint32_t CMP3 : 32; // 31:0
		} TMR_CMP3_bit;
	}; // 0x54

	/* PRU_IEP_TMR_CMP4 register bit field */
	union {
		volatile uint32_t TMR_CMP4;

		volatile struct {
			uint32_t CMP4 : 32; // 31:0
		} TMR_CMP4_bit;
	}; // 0x58

	/* PRU_IEP_TMR_CMP5 register bit field */
	union {
		volatile uint32_t TMR_CMP5;

		volatile struct {
			uint32_t CMP5 : 32; // 31:0
		} TMR_CMP5_bit;
	}; // 0x5c

	/* PRU_IEP_TMR_CMP6 register bit field */
	union {
		volatile uint32_t TMR_CMP6;

		volatile struct {
			uint32_t CMP6 : 32; // 31:0
		} TMR_CMP6_bit;
	}; // 0x60

	/* PRU_IEP_TMR_CMP7 register bit field */
	union {
		volatile uint32_t TMR_CMP7;

		volatile struct {
			uint32_t CMP7 : 32; // 31:0
		} TMR_CMP7_bit;
	}; // 0x64

	uint8_t rsvd68[32]; // 0x68 - 0x87

	/* PRU_IEP_TMR_CMP8 register bit field */
	union {
		volatile uint32_t TMR_CMP8;

		volatile struct {
			uint32_t CMP8 : 32; // 31:0
		} TMR_CMP8_bit;
	}; // 0x88

	/* PRU_IEP_TMR_CMP9 register bit field */
	union {
		volatile uint32_t TMR_CMP9;

		volatile struct {
			uint32_t CMP9 : 32; // 31:0
		} TMR_CMP9_bit;
	}; // 0x8c

	/* PRU_IEP_TMR_CMP10 register bit field */
	union {
		volatile uint32_t TMR_CMP10;

		volatile struct {
			uint32_t CMP10 : 32; // 31:0
		} TMR_CMP10_bit;
	}; // 0x90

	/* PRU_IEP_TMR_CMP11 register bit field */
	union {
		volatile uint32_t TMR_CMP11;

		volatile struct {
			uint32_t CMP11 : 32; // 31:0
		} TMR_CMP11_bit;
	}; // 0x94

	/* PRU_IEP_TMR_CMP12 register bit field */
	union {
		volatile uint32_t TMR_CMP12;

		volatile struct {
			uint32_t CMP12 : 32; // 31:0
		} TMR_CMP12_bit;
	}; // 0x98

	/* PRU_IEP_TMR_CMP13 register bit field */
	union {
		volatile uint32_t TMR_CMP13;

		volatile struct {
			uint32_t CMP13 : 32; // 31:0
		} TMR_CMP13_bit;
	}; // 0x9c

	/* PRU_IEP_TMR_CMP14 register bit field */
	union {
		volatile uint32_t TMR_CMP14;

		volatile struct {
			uint32_t CMP14 : 32; // 31:0
		} TMR_CMP14_bit;
	}; // 0xa0

	/* PRU_IEP_TMR_CMP15 register bit field */
	union {
		volatile uint32_t TMR_CMP15;

		volatile struct {
			uint32_t CMP15 : 32; // 31:0
		} TMR_CMP15_bit;
	}; // 0xa4

	/* PRU_IEP_TMR_CNT_RST register bit field */
	union {
		volatile uint32_t TMR_CNT_RST;

		volatile struct {
			uint32_t RESET_VAL : 32; // 31:0
		} TMR_CNT_RST_bit;
	}; // 0xa8

	/* PRU_IEP_TMR_PWM register bit field */
	union {
		volatile uint32_t TMR_PWM;

		volatile struct {
			uint32_t PWM0_RST_CNT_EN : 1; // 0
			uint32_t PWM0_HIT : 1; // 1
			uint32_t PWM3_RST_CNT_EN : 1; // 2
			uint32_t PWM3_HIT : 1; // 3
			uint32_t rsvd4 : 28; // 31:4
		} TMR_PWM_bit;
	}; // 0xac

	uint8_t rsvdb0[592]; // 0xb0 - 0x2ff

	/* PRU_IEP_TMR_DIGIO_CTRL register bit field */
	union {
		volatile uint32_t TMR_DIGIO_CTRL;

		volatile struct {
			uint32_t OUTVALID_POL : 1; // 0
			uint32_t rsvd1 : 1; // 1
			uint32_t BIDI_MODE : 1; // 2
			uint32_t rsvd3 : 1; // 3
			uint32_t IN_MODE : 2; // 5:4
			uint32_t rsvd6 : 26; // 31:6
		} TMR_DIGIO_CTRL_bit;
	}; // 0x300

	uint8_t rsvd304[4]; // 0x304 - 0x307

	/* PRU_IEP_TMR_DIGIO_DATA_IN register bit field */
	union {
		volatile uint32_t TMR_DIGIO_DATA_IN;

		volatile struct {
			uint32_t DATA_IN : 32; // 31:0
		} TMR_DIGIO_DATA_IN_bit;
	}; // 0x308

	/* PRU_IEP_TMR_DIGIO_DATA_IN_RAW register bit field */
	union {
		volatile uint32_t TMR_DIGIO_DATA_IN_RAW;

		volatile struct {
			uint32_t DATA_IN_RAW : 32; // 31:0
		} TMR_DIGIO_DATA_IN_RAW_bit;
	}; // 0x30c

	/* PRU_IEP_TMR_DIGIO_DATA_OUT register bit field */
	union {
		volatile uint32_t TMR_DIGIO_DATA_OUT;

		volatile struct {
			uint32_t DATA_OUT : 32; // 31:0
		} TMR_DIGIO_DATA_OUT_bit;
	}; // 0x310

	/* PRU_IEP_TMR_DIGIO_DATA_OUT_EN register bit field */
	union {
		volatile uint32_t TMR_DIGIO_DATA_OUT_EN;

		volatile struct {
			uint32_t DATA_OUT_EN : 32; // 31:0
		} TMR_DIGIO_DATA_OUT_EN_bit;
	}; // 0x314

	/* PRU_IEP_TMR_DIGIO_EXP register bit field */
	union {
		volatile uint32_t TMR_DIGIO_EXP;

		volatile struct {
			uint32_t SW_DATA_OUT_UPDATE : 1; // 0
			uint32_t OUTVALID_OVR_EN : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} TMR_DIGIO_EXP_bit;
	}; // 0x318

} pruIep;

volatile __far pruIep CT_IEP __attribute__((cregister("PRU_IEP", far), peripheral));

#endif /* _PRU_IEP_H_ */

