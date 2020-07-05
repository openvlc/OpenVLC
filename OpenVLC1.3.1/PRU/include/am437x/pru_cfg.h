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

#ifndef _PRU_CFG_H_
#define _PRU_CFG_H_

/* PRU CFG register set */
typedef struct {

	/* PRU_CFG_REVID register bit field */
	union {
		volatile uint32_t REVID;

		volatile struct {
			uint32_t REVID : 32; // 31:0
		} REVID_bit;
	}; // 0x0

	/* PRU_CFG_SYSCFG register bit field */
	union {
		volatile uint32_t SYSCFG;

		volatile struct {
			uint32_t IDLE_MODE : 2; // 1:0
			uint32_t STANDBY_MODE : 2; // 3:2
			uint32_t STANDBY_INIT : 1; // 4
			uint32_t SUB_MWAIT : 1; // 5
			uint32_t rsvd6 : 26; // 31:6
		} SYSCFG_bit;
	}; // 0x4

	/* PRU_CFG_GPCFG0 register bit field */
	union {
		volatile uint32_t GPCFG0;

		volatile struct {
			uint32_t PRU0_GPI_MODE : 2; // 1:0
			uint32_t PRU0_GPI_CLK_MODE : 1; // 2
			uint32_t PRU0_GPI_DIV0 : 5; // 7:3
			uint32_t PRU0_GPI_DIV1 : 5; // 12:8
			uint32_t PRU0_GPI_SB : 1; // 13
			uint32_t PRU0_GPO_MODE : 1; // 14
			uint32_t PRU0_GPO_DIV0 : 5; // 19:15
			uint32_t PRU0_GPO_DIV1 : 5; // 24:20
			uint32_t PRU0_GPO_SH_SEL : 1; // 25
			uint32_t PR1_PRU0_GP_MUX_SEL : 2; // 27:26
			uint32_t rsvd28 : 4; // 31:28
		} GPCFG0_bit;
	}; // 0x8

	/* PRU_CFG_GPCFG1 register bit field */
	union {
		volatile uint32_t GPCFG1;

		volatile struct {
			uint32_t PRU1_GPI_MODE : 2; // 1:0
			uint32_t PRU1_GPI_CLK_MODE : 1; // 2
			uint32_t PRU1_GPI_DIV0 : 5; // 7:3
			uint32_t PRU1_GPI_DIV1 : 5; // 12:8
			uint32_t PRU1_GPI_SB : 1; // 13
			uint32_t PRU1_GPO_MODE : 1; // 14
			uint32_t PRU1_GPO_DIV0 : 5; // 19:15
			uint32_t PRU1_GPO_DIV1 : 5; // 24:20
			uint32_t PRU1_GPO_SH_SEL : 1; // 25
			uint32_t PR1_PRU1_GP_MUX_SEL : 2; // 27:26
			uint32_t rsvd28 : 4; // 31:28
		} GPCFG1_bit;
	}; // 0xc

	/* PRU_CFG_CGR register bit field */
	union {
		volatile uint32_t CGR;

		volatile struct {
			uint32_t PRU0_CLK_STOP_REQ : 1; // 0
			uint32_t PRU0_CLK_STOP_ACK : 1; // 1
			uint32_t PRU0_CLK_EN : 1; // 2
			uint32_t PRU1_CLK_STOP_REQ : 1; // 3
			uint32_t PRU1_CLK_STOP_ACK : 1; // 4
			uint32_t PRU1_CLK_EN : 1; // 5
			uint32_t INTC_CLK_STOP_REQ : 1; // 6
			uint32_t INTC_CLK_STOP_ACK : 1; // 7
			uint32_t INTC_CLK_EN : 1; // 8
			uint32_t UART_CLK_STOP_REQ : 1; // 9
			uint32_t UART_CLK_STOP_ACK : 1; // 10
			uint32_t UART_CLK_EN : 1; // 11
			uint32_t ECAP_CLK_STOP_REQ : 1; // 12
			uint32_t ECAP_CLK_STOP_ACK : 1; // 13
			uint32_t ECAP_CLK_EN : 1; // 14
			uint32_t IEP_CLK_STOP_REQ : 1; // 15
			uint32_t IEP_CLK_STOP_ACK : 1; // 16
			uint32_t IEP_CLK_EN : 1; // 17
			uint32_t rsvd18 : 14; // 31:18
		} CGR_bit;
	}; // 0x10

	/* PRU_CFG_ISRP register bit field */
	union {
		volatile uint32_t ISRP;

		volatile struct {
			uint32_t PRU0_IMEM_PE_RAW : 4; // 3:0
			uint32_t PRU0_DMEM_PE_RAW : 4; // 7:4
			uint32_t PRU1_IMEM_PE_RAW : 4; // 11:8
			uint32_t PRU1_DMEM_PE_RAW : 4; // 15:12
			uint32_t RAM_PE_RAW : 4; // 19:16
			uint32_t rsvd20 : 12; // 31:20
		} ISRP_bit;
	}; // 0x14

	/* PRU_CFG_ISP register bit field */
	union {
		volatile uint32_t ISP;

		volatile struct {
			uint32_t PRU0_IMEM_PE : 4; // 3:0
			uint32_t PRU0_DMEM_PE : 4; // 7:4
			uint32_t PRU1_IMEM_PE : 4; // 11:8
			uint32_t PRU1_DMEM_PE : 4; // 15:12
			uint32_t RAM_PE : 4; // 19:16
			uint32_t rsvd20 : 12; // 31:20
		} ISP_bit;
	}; // 0x18

	/* PRU_CFG_IESP register bit field */
	union {
		volatile uint32_t IESP;

		volatile struct {
			uint32_t PRU0_IMEM_PE_SET : 4; // 3:0
			uint32_t PRU0_DMEM_PE_SET : 4; // 7:4
			uint32_t PRU1_IMEM_PE_SET : 4; // 11:8
			uint32_t PRU1_DMEM_PE_SET : 4; // 15:12
			uint32_t RAM_PE_SET : 4; // 19:16
			uint32_t rsvd20 : 12; // 31:20
		} IESP_bit;
	}; // 0x1c

	/* PRU_CFG_IECP register bit field */
	union {
		volatile uint32_t IECP;

		volatile struct {
			uint32_t PRU0_IMEM_PE_CLR : 4; // 3:0
			uint32_t PRU0_DMEM_PE_CLR : 4; // 7:4
			uint32_t PRU1_IMEM_PE_CLR : 4; // 11:8
			uint32_t PRU1_DMEM_PE_CLR : 4; // 15:12
			uint32_t rsvd16 : 16; // 31:16
		} IECP_bit;
	}; // 0x20

	uint8_t rsvd24[4]; // 0x24 - 0x27

	/* PRU_CFG_PMAO register bit field */
	union {
		volatile uint32_t PMAO;

		volatile struct {
			uint32_t PMAO_PRU0 : 1; // 0
			uint32_t PMAO_PRU1 : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} PMAO_bit;
	}; // 0x28

	uint8_t rsvd2c[4]; // 0x2c - 0x2f

	/* PRU_CFG_IEPCLK register bit field */
	union {
		volatile uint32_t IEPCLK;

		volatile struct {
			uint32_t OCP_EN : 1; // 0
			uint32_t rsvd1 : 31; // 31:1
		} IEPCLK_bit;
	}; // 0x30

	/* PRU_CFG_SPP register bit field */
	union {
		volatile uint32_t SPP;

		volatile struct {
			uint32_t PRU1_PAD_HP_EN : 1; // 0
			uint32_t XFR_SHIFT_EN : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} SPP_bit;
	}; // 0x34

	uint8_t rsvd38[8]; // 0x38 - 0x3f

	/* PRU_CFG_PIN_MX register bit field */
	union {
		volatile uint32_t PIN_MX;

		volatile struct {
			uint32_t PIN_MUX_SEL : 8; // 7:0
			uint32_t PWM0_REMAP_EN : 1; // 8
			uint32_t PWM3_REMAP_EN : 1; // 9
			uint32_t rsvd10 : 22; // 31:10
		} PIN_MX_bit;
	}; // 0x40

	uint8_t rsvd44[4]; // 0x44 - 0x47

	volatile struct {
		union {
			volatile uint32_t CLKSEL;

			volatile struct {
				unsigned CLK_SEL			: 2;		//1:0
				unsigned CLK_INV			: 1;		//2
				unsigned rsvd3				: 1;		//3
				unsigned ACC2_SEL			: 1;		//4
				unsigned rsvd5				: 27;		//31:5
			} CLKSEL_bit;
		};
		union {
			volatile uint32_t SS;

			volatile struct {
				unsigned SAMPLE_SIZE		: 8;		//7:0
				unsigned rsvd8				: 16;		//31:8
			} SS_bit;
		};
	} SD_PRU0[9];

	volatile struct {
		union {
			volatile uint32_t CLKSEL;

			volatile struct {
				unsigned CLK_SEL			: 2;		//1:0
				unsigned CLK_INV			: 1;		//2
				unsigned ACC2_SEL			: 1;		//3
				unsigned rsvd4				: 28;		//31:4
			} CLKSEL_bit;
		};
		union {
			volatile uint32_t SS;

			volatile struct {
				unsigned SAMPLE_SIZE		: 8;		//7:0
				unsigned rsvd8				: 16;		//31:8
			} SS_bit;
		};
	} SD_PRU1[9];

	uint8_t rsvddc[4]; // 0xdc - 0xdf

	/* PRU_CFG_ED_PRU0_RXCFG register bit field */
	union {
		volatile uint32_t ED_PRU0_RXCFG;

		volatile struct {
			uint32_t RX_SAMPLE_SIZE		: 3;	// 2:0
			uint32_t rsvd3					: 1;	//3
			uint32_t RX_CLK_SEL				: 1;	//4
			uint32_t rsvd5					: 10;	//14:5
			uint32_t RX_DIV_FACTOR_FRAC		: 1;	//15
			uint32_t RX_DIV_FACTOR			: 16;	//31:16
		} ED_PRU0_RXCFG_bit;
	}; // 0xe0

	/* PRU_CFG_ED_PRU0_TXCFG register bit field */
	union {
		volatile uint32_t ED_PRU0_TXCFG;

		volatile struct {
			uint32_t rsvd0					: 4;	// 3:0
			uint32_t TX_CLK_SEL			: 1;	// 4
			uint32_t TX_BUSY0				: 1;	// 5
			uint32_t TX_BUSY1				: 1;	// 6
			uint32_t TX_BUSY2				: 1;	// 7
			uint32_t PRU0_ENDAT0_CLK		: 1;	// 8
			uint32_t PRU0_ENDAT1_CLK		: 1;	// 9
			uint32_t PRU0_ENDAT2_CLK		: 1;	// 10
			uint32_t rsvd11				: 4;	// 14:11
			uint32_t TX_DIV_FACTOR_FRAC		: 1;	// 15
			uint32_t TX_DIV_FACTOR			: 16;	// 31:16
		} ED_PRU0_TXCFG_bit;
	}; // 0xe4

	/* PRU_CFG_ED_PRU0_CFG0_0 register bit field */
	union {
		volatile uint32_t ED_PRU0_CFG0_0;

		volatile struct {
			uint32_t TX_WIRE_DLY			: 11;	// 10:0
			uint32_t TX_FRAME_SIZE			: 5;	// 15:11
			uint32_t RX_FRAME_SIZE			: 12;	// 27-16
			uint32_t PRU0_ED0_RX_SNOOP		: 1;	// 28
			uint32_t ED_CLK_OUT_OVERRIDE_EN	: 1;	// 29
			uint32_t PRU0_ED0_CLK			: 1;	// 30
			uint32_t TX_FIFO_SWAP_BITS		: 1;	// 31
		} ED_PRU0_CFG0_0_bit;
	}; // 0xe8

	/* PRU_CFG_ED_PRU0_CFG1_0 register bit field */
	union {
		volatile uint32_t ED_PRU0_CFG1_0;

		volatile struct {
			uint32_t TST_DELAY_COUNTER		: 16;	// 15:0
			uint32_t RX_EN_COUNTER			: 16;	// 31:16
		} ED_PRU0_CFG1_0_bit;
	}; // 0xec

	/* PRU_CFG_ED_PRU0_CFG0_1 register bit field */
	union {
		volatile uint32_t ED_PRU0_CFG0_1;

		volatile struct {
			uint32_t TX_WIRE_DLY			: 11;	// 10:0
			uint32_t TX_FRAME_SIZE			: 5;	// 15:11
			uint32_t RX_FRAME_SIZE			: 12;	// 27-16
			uint32_t PRU0_ED1_RX_SNOOP		: 1;	// 28
			uint32_t ED_CLK_OUT_OVERRIDE_EN	: 1;	// 29
			uint32_t PRU0_ED1_CLK			: 1;	// 30
			uint32_t TX_FIFO_SWAP_BITS		: 1;	// 31
		} ED_PRU0_CFG0_1_bit;
	}; // 0xf0

	/* PRU_CFG_ED_PRU0_CFG1_1 register bit field */
	union {
		volatile uint32_t ED_PRU0_CFG1_1;

		volatile struct {
			uint32_t TST_DELAY_COUNTER		: 16;	// 15:0
			uint32_t RX_EN_COUNTER			: 16;	// 31:16
		} ED_PRU0_CFG1_1_bit;
	}; // 0xf4

	/* PRU_CFG_ED_PRU0_CFG0_2 register bit field */
	union {
		volatile uint32_t ED_PRU0_CFG0_2;

		volatile struct {
			uint32_t TX_WIRE_DLY			: 11;	// 10:0
			uint32_t TX_FRAME_SIZE			: 5;	// 15:11
			uint32_t RX_FRAME_SIZE			: 12;	// 27-16
			uint32_t PRU0_ED2_RX_SNOOP		: 1;	// 28
			uint32_t ED_CLK_OUT_OVERRIDE_EN	: 1;	// 29
			uint32_t PRU0_ED2_CLK			: 1;	// 30
			uint32_t TX_FIFO_SWAP_BITS		: 1;	// 31
		} ED_PRU0_CFG0_2_bit;
	}; // 0xf8

	/* PRU_CFG_ED_PRU0_CFG1_2 register bit field */
	union {
		volatile uint32_t ED_PRU0_CFG1_2;

		volatile struct {
			uint32_t TST_DELAY_COUNTER		: 16;	// 15:0
			uint32_t RX_EN_COUNTER			: 16;	// 31:16
		} ED_PRU0_CFG1_2_bit;
	}; // 0xfc

	/* PRU_CFG_ED_PRU1_RXCFG register bit field */
	union {
		volatile uint32_t ED_PRU1_RXCFG;

		volatile struct {
			uint32_t RX_SAMPLE_SIZE		: 3;	// 2:0
			uint32_t RX_CLK_SEL				: 1;	//3
			uint32_t RX_DIV_FACTOR_FRAC		: 1;	//4
			uint32_t RX_DIV_FACTOR			: 16;	//20:5
			uint32_t rsvd21					: 11;	//31:21
		} ED_PRU1_RXCFG_bit;
	}; // 0x100

	/* PRU_CFG_ED_PRU1_TXCFG register bit field */
	union {
		volatile uint32_t ED_PRU1_TXCFG;

		volatile struct {
			uint32_t TX_CLK_SEL			: 1;	// 0
			uint32_t TX_BUSY0				: 1;	// 1
			uint32_t TX_BUSY1				: 1;	// 2
			uint32_t TX_BUSY2				: 1;	// 3
			uint32_t PRU1_ENDAT0_CLK		: 1;	// 4
			uint32_t PRU1_ENDAT1_CLK		: 1;	// 5
			uint32_t PRU1_ENDAT2_CLK		: 1;	// 6
			uint32_t TX_DIV_FACTOR_FRAC		: 1;	// 7
			uint32_t TX_DIV_FACTOR			: 16;	// 23:8
			uint32_t rsvd24					: 8;	// 31:24
		} ED_PRU1_TXCFG_bit;
	}; // 0x104

	/* PRU_CFG_ED_PRU1_CFG0_0 register bit field */
	union {
		volatile uint32_t ED_PRU1_CFG0_0;

		volatile struct {
			uint32_t TX_WIRE_DLY			: 11;	// 10:0
			uint32_t TX_FRAME_SIZE			: 5;	// 15:11
			uint32_t RX_FRAME_SIZE			: 12;	// 27-16
			uint32_t PRU1_ED0_RX_SNOOP		: 1;	// 28
			uint32_t ED_CLK_OUT_OVERRIDE_EN	: 1;	// 29
			uint32_t PRU1_ED0_CLK			: 1;	// 30
			uint32_t TX_FIFO_SWAP_BITS		: 1;	// 31
		} ED_PRU1_CFG0_0_bit;
	}; // 0x108

	/* PRU_CFG_ED_PRU1_CFG1_0 register bit field */
	union {
		volatile uint32_t ED_PRU1_CFG1_0;

		volatile struct {
			uint32_t TST_DELAY_COUNTER		: 16;	// 15:0
			uint32_t RX_EN_COUNTER			: 16;	// 31:16
		} ED_PRU1_CFG1_0_bit;
	}; // 0x10c

	/* PRU_CFG_ED_PRU1_CFG0_1 register bit field */
	union {
		volatile uint32_t ED_PRU1_CFG0_1;

		volatile struct {
			uint32_t TX_WIRE_DLY			: 11;	// 10:0
			uint32_t TX_FRAME_SIZE			: 5;	// 15:11
			uint32_t RX_FRAME_SIZE			: 12;	// 27-16
			uint32_t PRU1_ED1_RX_SNOOP		: 1;	// 28
			uint32_t ED_CLK_OUT_OVERRIDE_EN	: 1;	// 29
			uint32_t PRU1_ED1_CLK			: 1;	// 30
			uint32_t TX_FIFO_SWAP_BITS		: 1;	// 31
		} ED_PRU1_CFG0_1_bit;
	}; // 0x110

	/* PRU_CFG_ED_PRU1_CFG1_1 register bit field */
	union {
		volatile uint32_t ED_PRU1_CFG1_1;

		volatile struct {
			uint32_t TST_DELAY_COUNTER		: 16;	// 15:0
			uint32_t RX_EN_COUNTER			: 16;	// 31:16
		} ED_PRU1_CFG1_1_bit;
	}; // 0x114

	/* PRU_CFG_ED_PRU1_CFG0_2 register bit field */
	union {
		volatile uint32_t ED_PRU1_CFG0_2;

		volatile struct {
			uint32_t TX_WIRE_DLY			: 11;	// 10:0
			uint32_t TX_FRAME_SIZE			: 5;	// 15:11
			uint32_t RX_FRAME_SIZE			: 12;	// 27-16
			uint32_t PRU1_ED2_RX_SNOOP		: 1;	// 28
			uint32_t ED_CLK_OUT_OVERRIDE_EN	: 1;	// 29
			uint32_t PRU1_ED2_CLK			: 1;	// 30
			uint32_t TX_FIFO_SWAP_BITS		: 1;	// 31
		} ED_PRU1_CFG0_2_bit;
	}; // 0x118

	/* PRU_CFG_ED_PRU1_CFG1_2 register bit field */
	union {
		volatile uint32_t ED_PRU1_CFG1_2;

		volatile struct {
			uint32_t TST_DELAY_COUNTER		: 16;	// 15:0
			uint32_t RX_EN_COUNTER			: 16;	// 31:16
		} ED_PRU1_CFG1_2_bit;
	}; // 0x11c

} pruCfg;

volatile __far pruCfg CT_CFG __attribute__((cregister("PRU_CFG", near), peripheral));

#endif /* _PRU_CFG_H_ */

