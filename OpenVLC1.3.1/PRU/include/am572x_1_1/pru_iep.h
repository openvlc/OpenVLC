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
			unsigned CNT_EN : 1;		// 0
			unsigned rsvd1 : 3;		// 3:1
			unsigned DEFAULT_INC : 4;	// 7:4
			unsigned CMP_INC : 12;		// 19:8
			unsigned rsvd12 : 12;		// 31:20
		} GLB_CFG_bit;
	};	// 0x0


	/* PRU_IEP_GLB_STS register bit field */
	union {
		volatile uint32_t GLB_STS;

		volatile struct {
			unsigned CNT_OVF : 1;		// 0
			unsigned rsvd1 : 31;		// 31:1
		} GLB_STS_bit;
	};	// 0x4


	/* PRU_IEP_COMPEN register bit field */
	union {
		volatile uint32_t COMPEN;

		volatile struct {
			unsigned COMPEN_CNT : 23;	// 22:0
			unsigned rsvd24 : 9;		// 31:23
		} COMPEN_bit;
	};	// 0x8


	/* PRU_IEP_CNT register bit field */
	union {
		volatile uint32_t CNT;

		volatile struct {
			unsigned COUNT : 32;		// 31:0
		} CNT_bit;
	};	// 0xC


	uint32_t rsvd10[12];		// 0x10 - 0x3C


	/* PRU_IEP_CMP_CFG register bit field */
	union {
		volatile uint32_t CMP_CFG;

		volatile struct {
			unsigned CMP0_RST_CNT_EN : 1;	// 0
			unsigned CMP_EN : 8;		// 8:1
			unsigned rsvd9 : 23;		// 31:9
		} CMP_CFG_bit;
	};	// 0x40


	/* PRU_IEP_CMP_STS register bit field */
	union {
		volatile uint32_t CMP_STS;

		volatile struct {
			unsigned CMP_HIT : 8;		// 7:0
			unsigned rsvd12 : 24;		// 31:8
		} CMP_STS_bit;
	};	// 0x44

	/* PRU_IEP_CMP0 register bit field */
	union {
		volatile uint32_t CMP0;

		volatile struct {
			unsigned CMP0 : 32;		// 31:0
		} CMP0_bit;
	};	// 0x48


	/* PRU_IEP_CMP1 register bit field */
	union {
		volatile uint32_t CMP1;

		volatile struct {
			unsigned CMP1 : 32;		// 31:0
		} CMP1_bit;
	};	// 0x4C


	/* PRU_IEP_CMP2 register bit field */
	union {
		volatile uint32_t CMP2;

		volatile struct {
			unsigned CMP2 : 32;		// 31:0
		} CMP2_bit;
	};	// 0x50


	/* PRU_IEP_CMP3 register bit field */
	union {
		volatile uint32_t CMP3;

		volatile struct {
			unsigned CMP3 : 32;		// 31:0
		} CMP3_bit;
	};	// 0x54


	/* PRU_IEP_CMP4 register bit field */
	union {
		volatile uint32_t CMP4;

		volatile struct {
			unsigned CMP4 : 32;		// 31:0
		} CMP4_bit;
	};	// 0x58


	/* PRU_IEP_CMP5 register bit field */
	union {
		volatile uint32_t CMP5;

		volatile struct {
			unsigned CMP5 : 32;		// 31:0
		} CMP5_bit;
	};	// 0x5C


	/* PRU_IEP_CMP6 register bit field */
	union {
		volatile uint32_t CMP6;

		volatile struct {
			unsigned CMP6 : 32;		// 31:0
		} CMP6_bit;
	};	// 0x60


	/* PRU_IEP_CMP7 register bit field */
	union {
		volatile uint32_t CMP7;

		volatile struct {
			unsigned CMP7 : 32;		// 31:0
		} CMP7_bit;
	};	// 0x64

	uint32_t rsvd68[166];            // 0x68 - 0x2FF

	/* PRU_IEP_DIGIO_CTRL register bit field */
	union {
		volatile uint32_t DIGIO_CTRL;

		volatile struct {
			unsigned OUTVALID_POL	: 1;	// 0
			unsigned OUTVALID_MODE	: 1;	// 1
			unsigned BIDI_MODE		: 1;	// 2
			unsigned WD_MODE		: 1;	// 3
			unsigned IN_MODE		: 2;	// 5:4
			unsigned OUT_MODE		: 2;	// 7:6
			unsigned RESERVED8		: 24;	// 31:8
		} DIGIO_CTRL_bit;
	}; // 0x300

	uint32_t rsvd304[1];            // 0x304

	/* PRU_IEP_DIGIO_DATA_IN register bit field */
	union {
		volatile uint32_t DIGIO_DATA_IN;

		volatile struct {
			unsigned DATA_IN : 32;           // 31:0
		} DIGIO_DATA_IN_bit;
	}; // 0x308

	/* PRU_IEP_DIGIO_DATA_IN_RAW register bit field */
	union {
		volatile uint32_t DIGIO_DATA_IN_RAW;

		volatile struct {
			unsigned DATA_IN_RAW : 32;       // 31:0
		} DIGIO_DATA_IN_RAW_bit;
	}; // 0x30C

	/* PRU_IEP_DIGIO_DATA_OUT register bit field */
	union {
		volatile uint32_t DIGIO_DATA_OUT;

		volatile struct {
			unsigned DATA_OUT : 32;           // 31:0
		} DIGIO_DATA_OUT_bit;
	}; // 0x310

	/* PRU_IEP_DIGIO_DATA_OUT_EN register bit field */
	union {
		volatile uint32_t DIGIO_DATA_OUT_EN;

		volatile struct {
			unsigned DATA_OUT_EN : 32;        // 31:0
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
