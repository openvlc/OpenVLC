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

	/* PRU_IEP_GLB_CFG register bit field */
	union {
		volatile uint32_t GLB_CFG;

		volatile struct {
			uint32_t CNT_ENABLE : 1; // 0
			uint32_t rsvd1 : 3; // 3:1
			uint32_t DEFAULT_INC : 4; // 7:4
			uint32_t CMP_INC : 12; // 19:8
			uint32_t rsvd20 : 12; // 31:20
		} GLB_CFG_bit;
	}; // 0x0

	/* PRU_IEP_GLB_STS register bit field */
	union {
		volatile uint32_t GLB_STS;

		volatile struct {
			uint32_t CNT_OVF : 1; // 0
			uint32_t rsvd1 : 31; // 31:1
		} GLB_STS_bit;
	}; // 0x4

	/* PRU_IEP_COMPEN register bit field */
	union {
		volatile uint32_t COMPEN;

		volatile struct {
			uint32_t COMPEN_CNT : 23; // 22:0
			uint32_t rsvd24 : 9; // 31:23
		} COMPEN_bit;
	}; // 0x8

	/* PRU_IEP_SLOW_COMPEN register bit field */
	union {
		volatile uint32_t SLOW_COMPEN;

		volatile struct {
			uint32_t SLOW_COMPEN_CNT : 32; // 31:0
		} SLOW_COMPEN_bit;
	}; // 0xc

	/* PRU_IEP_LOW_COUNTER register bit field */
	union {
		volatile uint32_t LOW_COUNTER;

		volatile struct {
			uint32_t COUNT : 32; // 31:0
		} LOW_COUNTER_bit;
	}; // 0x10

	/* PRU_IEP_HIGH_COUNTER register bit field */
	union {
		volatile uint32_t HIGH_COUNTER;

		volatile struct {
			uint32_t COUNT : 32; // 31:0
		} HIGH_COUNTER_bit;
	}; // 0x14

	uint8_t rsvd18[88]; //0x18 - 0x6f

	/* PRU_IEP_CMP_CFG register bit field */
	union {
		volatile uint32_t CMP_CFG;

		volatile struct {
			uint32_t CMP0_RST_CNT_EN : 1; // 0
			uint32_t CMP_EN : 16; // 16:1
			uint32_t rsvd17 : 15; // 31:17
		} CMP_CFG_bit;
	}; // 0x70

	/* PRU_IEP_CMP_STS register bit field */
	union {
		volatile uint32_t CMP_STS;

		volatile struct {
			uint32_t CMP_HIT : 16; // 15:0
			uint32_t rsvd16 : 16; // 31:16
		} CMP_STS_bit;
	}; // 0x74

	/* PRU_IEP_CMP0_0 register bit field */
	union {
		volatile uint32_t CMP0_0;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_0_bit;
	}; // 0x78

	/* PRU_IEP_CMP1_0 register bit field */
	union {
		volatile uint32_t CMP1_0;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_0_bit;
	}; // 0x7c

	/* PRU_IEP_CMP0_1 register bit field */
	union {
		volatile uint32_t CMP0_1;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_1_bit;
	}; // 0x80

	/* PRU_IEP_CMP1_1 register bit field */
	union {
		volatile uint32_t CMP1_1;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_1_bit;
	}; // 0x84

	/* PRU_IEP_CMP0_2 register bit field */
	union {
		volatile uint32_t CMP0_2;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_2_bit;
	}; // 0x88

	/* PRU_IEP_CMP1_2 register bit field */
	union {
		volatile uint32_t CMP1_2;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_2_bit;
	}; // 0x8c

	/* PRU_IEP_CMP0_3 register bit field */
	union {
		volatile uint32_t CMP0_3;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_3_bit;
	}; // 0x90

	/* PRU_IEP_CMP1_3 register bit field */
	union {
		volatile uint32_t CMP1_3;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_3_bit;
	}; // 0x94

	/* PRU_IEP_CMP0_4 register bit field */
	union {
		volatile uint32_t CMP0_4;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_4_bit;
	}; // 0x98

	/* PRU_IEP_CMP1_4 register bit field */
	union {
		volatile uint32_t CMP1_4;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_4_bit;
	}; // 0x9c

	/* PRU_IEP_CMP0_5 register bit field */
	union {
		volatile uint32_t CMP0_5;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_5_bit;
	}; // 0xa0

	/* PRU_IEP_CMP1_5 register bit field */
	union {
		volatile uint32_t CMP1_5;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_5_bit;
	}; // 0xa4

	/* PRU_IEP_CMP0_6 register bit field */
	union {
		volatile uint32_t CMP0_6;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_6_bit;
	}; // 0xa8

	/* PRU_IEP_CMP1_6 register bit field */
	union {
		volatile uint32_t CMP1_6;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_6_bit;
	}; // 0xac

	/* PRU_IEP_CMP0_7 register bit field */
	union {
		volatile uint32_t CMP0_7;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_7_bit;
	}; // 0xb0

	/* PRU_IEP_CMP1_7 register bit field */
	union {
		volatile uint32_t CMP1_7;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_7_bit;
	}; // 0xb4

	uint8_t rsvdb8[8]; //0xb8 - 0xbf

	/* PRU_IEP_CMP0_8 register bit field */
	union {
		volatile uint32_t CMP0_8;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_8_bit;
	}; // 0xc0

	/* PRU_IEP_CMP1_8 register bit field */
	union {
		volatile uint32_t CMP1_8;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_8_bit;
	}; // 0xc4

	/* PRU_IEP_CMP0_9 register bit field */
	union {
		volatile uint32_t CMP0_9;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_9_bit;
	}; // 0xc8

	/* PRU_IEP_CMP1_9 register bit field */
	union {
		volatile uint32_t CMP1_9;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_9_bit;
	}; // 0xcc

	/* PRU_IEP_CMP0_10 register bit field */
	union {
		volatile uint32_t CMP0_10;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_10_bit;
	}; // 0xd0

	/* PRU_IEP_CMP1_10 register bit field */
	union {
		volatile uint32_t CMP1_10;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_10_bit;
	}; // 0xd4

	/* PRU_IEP_CMP0_11 register bit field */
	union {
		volatile uint32_t CMP0_11;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_11_bit;
	}; // 0xd8

	/* PRU_IEP_CMP1_11 register bit field */
	union {
		volatile uint32_t CMP1_11;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_11_bit;
	}; // 0xdc

	/* PRU_IEP_CMP0_12 register bit field */
	union {
		volatile uint32_t CMP0_12;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_12_bit;
	}; // 0xe0

	/* PRU_IEP_CMP1_12 register bit field */
	union {
		volatile uint32_t CMP1_12;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_12_bit;
	}; // 0xe4

	/* PRU_IEP_CMP0_13 register bit field */
	union {
		volatile uint32_t CMP0_13;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_13_bit;
	}; // 0xe8

	/* PRU_IEP_CMP1_13 register bit field */
	union {
		volatile uint32_t CMP1_13;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_13_bit;
	}; // 0xec

	/* PRU_IEP_CMP0_14 register bit field */
	union {
		volatile uint32_t CMP0_14;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_14_bit;
	}; // 0xf0

	/* PRU_IEP_CMP1_14 register bit field */
	union {
		volatile uint32_t CMP1_14;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_14_bit;
	}; // 0xf4

	/* PRU_IEP_CMP0_15 register bit field */
	union {
		volatile uint32_t CMP0_15;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP0_15_bit;
	}; // 0xf8

	/* PRU_IEP_CMP1_15 register bit field */
	union {
		volatile uint32_t CMP1_15;

		volatile struct {
			uint32_t CMP : 32; // 31:0
		} CMP1_15_bit;
	}; // 0xfc

	/* PRU_IEP_LOW_CNT_RST register bit field */
	union {
		volatile uint32_t LOW_CNT_RST;

		volatile struct {
			uint32_t RESET_VAL : 32; // 31:0
		} LOW_CNT_RST_bit;
	}; // 0x100

	/* PRU_IEP_HIGH_CNT_RST register bit field */
	union {
		volatile uint32_t HIGH_CNT_RST;

		volatile struct {
			uint32_t RESET_VAL : 32; // 31:0
		} HIGH_CNT_RST_bit;
	}; // 0x104

	/* PRU_IEP_PWM register bit field */
	union {
		volatile uint32_t PWM;

		volatile struct {
			uint32_t PWM0_RST_CNT_EN : 1; // 0
			uint32_t PWM0_HIT : 1; // 1
			uint32_t PWM3_RST_CNT_EN : 1; // 2
			uint32_t PWM3_HIT : 1; // 3
			uint32_t rsvd4 : 28; // 31:4
		} PWM_bit;
	}; // 0x108

	uint8_t rsvd10c[500]; // 0x10c - 0x2ff

	/* PRU_IEP_DIGIO_CTRL register bit field */
	union {
		volatile uint32_t DIGIO_CTRL;

		volatile struct {
			uint32_t OUTVALID_POL : 1; // 0
			uint32_t OUTVALID_MODE : 1; // 1
			uint32_t BIDI_MODE : 1; // 2
			uint32_t WD_MODE : 1; // 3
			uint32_t IN_MODE : 2; // 5:4
			uint32_t OUT_MODE : 2; // 7:6
			uint32_t rsvd8 : 24; // 31:8
		} DIGIO_CTRL_bit;
	}; // 0x300

	uint8_t rsvd304[4]; // 0x304 - 0x307

	/* PRU_IEP_DIGIO_DATA_IN register bit field */
	union {
		volatile uint32_t DIGIO_DATA_IN;

		volatile struct {
			uint32_t DATA_IN : 32; // 31:0
		} DIGIO_DATA_IN_bit;
	}; // 0x308

	/* PRU_IEP_DIGIO_DATA_IN_RAW register bit field */
	union {
		volatile uint32_t DIGIO_DATA_IN_RAW;

		volatile struct {
			uint32_t DATA_IN_RAW : 32; // 31:0
		} DIGIO_DATA_IN_RAW_bit;
	}; // 0x30c

	/* PRU_IEP_DIGIO_DATA_OUT register bit field */
	union {
		volatile uint32_t DIGIO_DATA_OUT;

		volatile struct {
			uint32_t DATA_OUT : 32; // 31:0
		} DIGIO_DATA_OUT_bit;
	}; // 0x310

	/* PRU_IEP_DIGIO_DATA_OUT_EN register bit field */
	union {
		volatile uint32_t DIGIO_DATA_OUT_EN;

		volatile struct {
			uint32_t DATA_OUT_EN : 32; // 31:0
		} DIGIO_DATA_OUT_EN_bit;
	}; // 0x314

	/* PRU_IEP_DIGIO_EXP register bit field */
	union {
		volatile uint32_t DIGIO_EXP;

		volatile struct {
			unsigned SW_DATA_OUT_UPDATE : 1;	// 0
			unsigned OUTVALID_OVR_EN	: 1;	// 1
			unsigned SW_OUTVALID		: 1;	// 2
			unsigned rsvd3				: 1;	// 3
			unsigned OUTVALID_DLY		: 4;	// 7:4
			unsigned SOF_DLY			: 4;	// 11:8
			unsigned SOF_SEL			: 1;	// 12
			unsigned EOF_SEL			: 1;	// 13
			unsigned rsvd14			: 18;	// 31:14
		} DIGIO_EXP_bit;
	}; // 0x318

} pruIep;

volatile __far pruIep CT_IEP __attribute__((cregister("PRU_IEP", far), peripheral));

#endif /* _PRU_IEP_H_ */

