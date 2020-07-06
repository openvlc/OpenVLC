/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef _SYS_ADC0_H_
#define _SYS_ADC0_H_

/* SYS ADC0 register set */
typedef struct {

	/* SYS_ADC0_REVISION register bit field */
	union {
		volatile uint32_t REVISION;

		volatile struct {
			uint32_t Y_MINOR : 6; // 5:0
			uint32_t CUSTOM : 2; // 7:6
			uint32_t X_MAJOR : 3; // 10:8
			uint32_t R_RTL : 5; // 15:11
			uint32_t FUNC : 12; // 27:16
			uint32_t rsvd28 : 2; // 29:28
			uint32_t SCHEME : 2; // 31:30
		} REVISION_bit;
	}; // 0x0

	uint8_t rsvd4[12]; // 0x4 - 0xf

	/* SYS_ADC0_SYSCONFIG register bit field */
	union {
		volatile uint32_t SYSCONFIG;

		volatile struct {
			uint32_t rsvd0 : 2; // 1:0
			uint32_t IDLEMODE : 2; // 3:2
			uint32_t rsvd4 : 28; // 31:4
		} SYSCONFIG_bit;
	}; // 0x10

	uint8_t rsvd14[16]; // 0x14 - 0x23

	/* SYS_ADC0_IRQSTS_RAW register bit field */
	union {
		volatile uint32_t IRQSTS_RAW;

		volatile struct {
			uint32_t HW_PEN_EVENT_ASYNCHRONOUS : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t PEN_UP_EVENT : 1; // 9
			uint32_t PEN_IRQ_SYNCHRONIZED : 1; // 10
			uint32_t rsvd11 : 21; // 31:11
		} IRQSTS_RAW_bit;
	}; // 0x24

	/* SYS_ADC0_IRQSTS register bit field */
	union {
		volatile uint32_t IRQSTS;

		volatile struct {
			uint32_t HW_PEN_EVENT_ASYNCHRONOUS : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t PEN_UP_EVENT : 1; // 9
			uint32_t HW_PEN_EVENT_SYNCHRONOUS : 1; // 10
			uint32_t rsvd11 : 21; // 31:11
		} IRQSTS_bit;
	}; // 0x28

	/* SYS_ADC0_IRQEN_SET register bit field */
	union {
		volatile uint32_t IRQEN_SET;

		volatile struct {
			uint32_t HW_PEN_EVENT_ASYNCHRONOUS : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t PEN_UP_EVENT : 1; // 9
			uint32_t HW_PEN_EVENT_SYNCHRONOUS : 1; // 10
			uint32_t rsvd11 : 21; // 31:11
		} IRQEN_SET_bit;
	}; // 0x2c

	/* SYS_ADC0_IRQEN_CLR register bit field */
	union {
		volatile uint32_t IRQEN_CLR;

		volatile struct {
			uint32_t HW_PEN_EVENT_ASYNCHRONOUS : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t PEN_UP_EVENT : 1; // 9
			uint32_t HW_PEN_EVENT_SYNCHRONOUS : 1; // 10
			uint32_t rsvd11 : 21; // 31:11
		} IRQEN_CLR_bit;
	}; // 0x30

	/* SYS_ADC0_IRQWAKEUP register bit field */
	union {
		volatile uint32_t IRQWAKEUP;

		volatile struct {
			uint32_t WAKEEN0 : 1; // 0
			uint32_t rsvd1 : 31; // 31:1
		} IRQWAKEUP_bit;
	}; // 0x34

	/* SYS_ADC0_DMAEN_SET register bit field */
	union {
		volatile uint32_t DMAEN_SET;

		volatile struct {
			uint32_t ENABLE_0 : 1; // 0
			uint32_t ENABLE_1 : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} DMAEN_SET_bit;
	}; // 0x38

	/* SYS_ADC0_DMAEN_CLR register bit field */
	union {
		volatile uint32_t DMAEN_CLR;

		volatile struct {
			uint32_t ENABLE_0 : 1; // 0
			uint32_t ENABLE_1 : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} DMAEN_CLR_bit;
	}; // 0x3c

	/* SYS_ADC0_CTRL register bit field */
	union {
		volatile uint32_t CTRL;

		volatile struct {
			uint32_t ENABLE : 1; // 0
			uint32_t STEP_ID_TAG : 1; // 1
			uint32_t STEPCONFIG_WRITEPROTECT_N_ACTIVE_LOW : 1; // 2
			uint32_t ADC_BIAS_SELECT : 1; // 3
			uint32_t POWER_DOWN : 1; // 4
			uint32_t AFE_PEN_CTRL : 2; // 6:5
			uint32_t TOUCH_SCREEN_ENABLE : 1; // 7
			uint32_t HW_EVENT_MAPPING : 1; // 8
			uint32_t HW_PREEMPT : 1; // 9
			uint32_t rsvd10 : 22; // 31:10
		} CTRL_bit;
	}; // 0x40

	/* SYS_ADC0_ADCSTAT register bit field */
	union {
		volatile uint32_t ADCSTAT;

		volatile struct {
			uint32_t STEP_ID : 5; // 4:0
			uint32_t FSM_BUSY : 1; // 5
			uint32_t PEN_IRQ0 : 1; // 6
			uint32_t PEN_IRQ1 : 1; // 7
			uint32_t rsvd8 : 24; // 31:8
		} ADCSTAT_bit;
	}; // 0x44

	/* SYS_ADC0_ADCRANGE register bit field */
	union {
		volatile uint32_t ADCRANGE;

		volatile struct {
			uint32_t LOW_RANGE_DATA : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t HIGH_RANGE_DATA : 12; // 27:16
			uint32_t rsvd28 : 4; // 31:28
		} ADCRANGE_bit;
	}; // 0x48

	/* SYS_ADC0_ADC_CLKDIV register bit field */
	union {
		volatile uint32_t ADC_CLKDIV;

		volatile struct {
			uint32_t ADC_CLKDIV : 16; // 15:0
			uint32_t rsvd16 : 16; // 31:16
		} ADC_CLKDIV_bit;
	}; // 0x4c

	/* SYS_ADC0_ADC_MISC register bit field */
	union {
		volatile uint32_t ADC_MISC;

		volatile struct {
			uint32_t AFE_SPARE_INPUT : 4; // 3:0
			uint32_t AFE_SPARE_OUTPUT : 4; // 7:4
			uint32_t rsvd8 : 24; // 31:8
		} ADC_MISC_bit;
	}; // 0x50

	/* SYS_ADC0_STEPEN register bit field */
	union {
		volatile uint32_t STEPEN;

		volatile struct {
			uint32_t TS_CHARGE : 1; // 0
			uint32_t STEP1 : 1; // 1
			uint32_t STEP2 : 1; // 2
			uint32_t STEP3 : 1; // 3
			uint32_t STEP4 : 1; // 4
			uint32_t STEP5 : 1; // 5
			uint32_t STEP6 : 1; // 6
			uint32_t STEP7 : 1; // 7
			uint32_t STEP8 : 1; // 8
			uint32_t STEP9 : 1; // 9
			uint32_t STEP10 : 1; // 10
			uint32_t STEP11 : 1; // 11
			uint32_t STEP12 : 1; // 12
			uint32_t STEP13 : 1; // 13
			uint32_t STEP14 : 1; // 14
			uint32_t STEP15 : 1; // 15
			uint32_t STEP16 : 1; // 16
			uint32_t rsvd17 : 15; // 31:17
		} STEPEN_bit;
	}; // 0x54

	/* SYS_ADC0_IDLECONFIG register bit field */
	union {
		volatile uint32_t IDLECONFIG;

		volatile struct {
			uint32_t rsvd0 : 5; // 4:0
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW__SWC : 1; // 6
			uint32_t YPPSW__SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t rsvd26 : 6; // 31:26
		} IDLECONFIG_bit;
	}; // 0x58

	/* SYS_ADC0_TS_CHARGE_STEPCONFIG register bit field */
	union {
		volatile uint32_t TS_CHARGE_STEPCONFIG;

		volatile struct {
			uint32_t rsvd0 : 5; // 4:0
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW__SWC : 1; // 6
			uint32_t YPPSW__SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t rsvd26 : 6; // 31:26
		} TS_CHARGE_STEPCONFIG_bit;
	}; // 0x5c

	/* SYS_ADC0_TS_CHARGE_DELAY register bit field */
	union {
		volatile uint32_t TS_CHARGE_DELAY;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 14; // 31:18
		} TS_CHARGE_DELAY_bit;
	}; // 0x60

	/* SYS_ADC0_STEPCONFIG0 register bit field */
	union {
		volatile uint32_t STEPCONFIG0;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG0_bit;
	}; // 0x64

	/* SYS_ADC0_STEPDELAY0 register bit field */
	union {
		volatile uint32_t STEPDELAY0;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY0_bit;
	}; // 0x68

	/* SYS_ADC0_STEPCONFIG1 register bit field */
	union {
		volatile uint32_t STEPCONFIG1;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG1_bit;
	}; // 0x6c

	/* SYS_ADC0_STEPDELAY1 register bit field */
	union {
		volatile uint32_t STEPDELAY1;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY1_bit;
	}; // 0x70

	/* SYS_ADC0_STEPCONFIG2 register bit field */
	union {
		volatile uint32_t STEPCONFIG2;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG2_bit;
	}; // 0x74

	/* SYS_ADC0_STEPDELAY2 register bit field */
	union {
		volatile uint32_t STEPDELAY2;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY2_bit;
	}; // 0x78

	/* SYS_ADC0_STEPCONFIG3 register bit field */
	union {
		volatile uint32_t STEPCONFIG3;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG3_bit;
	}; // 0x7c

	/* SYS_ADC0_STEPDELAY3 register bit field */
	union {
		volatile uint32_t STEPDELAY3;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY3_bit;
	}; // 0x80

	/* SYS_ADC0_STEPCONFIG4 register bit field */
	union {
		volatile uint32_t STEPCONFIG4;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG4_bit;
	}; // 0x84

	/* SYS_ADC0_STEPDELAY4 register bit field */
	union {
		volatile uint32_t STEPDELAY4;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY4_bit;
	}; // 0x88

	/* SYS_ADC0_STEPCONFIG5 register bit field */
	union {
		volatile uint32_t STEPCONFIG5;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG5_bit;
	}; // 0x8c

	/* SYS_ADC0_STEPDELAY5 register bit field */
	union {
		volatile uint32_t STEPDELAY5;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY5_bit;
	}; // 0x90

	/* SYS_ADC0_STEPCONFIG6 register bit field */
	union {
		volatile uint32_t STEPCONFIG6;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG6_bit;
	}; // 0x94

	/* SYS_ADC0_STEPDELAY6 register bit field */
	union {
		volatile uint32_t STEPDELAY6;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY6_bit;
	}; // 0x98

	/* SYS_ADC0_STEPCONFIG7 register bit field */
	union {
		volatile uint32_t STEPCONFIG7;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG7_bit;
	}; // 0x9c

	/* SYS_ADC0_STEPDELAY7 register bit field */
	union {
		volatile uint32_t STEPDELAY7;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY7_bit;
	}; // 0xa0

	/* SYS_ADC0_STEPCONFIG8 register bit field */
	union {
		volatile uint32_t STEPCONFIG8;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG8_bit;
	}; // 0xa4

	/* SYS_ADC0_STEPDELAY8 register bit field */
	union {
		volatile uint32_t STEPDELAY8;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY8_bit;
	}; // 0xa8

	/* SYS_ADC0_STEPCONFIG9 register bit field */
	union {
		volatile uint32_t STEPCONFIG9;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG9_bit;
	}; // 0xac

	/* SYS_ADC0_STEPDELAY9 register bit field */
	union {
		volatile uint32_t STEPDELAY9;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY9_bit;
	}; // 0xb0

	/* SYS_ADC0_STEPCONFIG10 register bit field */
	union {
		volatile uint32_t STEPCONFIG10;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG10_bit;
	}; // 0xb4

	/* SYS_ADC0_STEPDELAY10 register bit field */
	union {
		volatile uint32_t STEPDELAY10;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY10_bit;
	}; // 0xb8

	/* SYS_ADC0_STEPCONFIG11 register bit field */
	union {
		volatile uint32_t STEPCONFIG11;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG11_bit;
	}; // 0xbc

	/* SYS_ADC0_STEPDELAY11 register bit field */
	union {
		volatile uint32_t STEPDELAY11;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY11_bit;
	}; // 0xc0

	/* SYS_ADC0_STEPCONFIG12 register bit field */
	union {
		volatile uint32_t STEPCONFIG12;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG12_bit;
	}; // 0xc4

	/* SYS_ADC0_STEPDELAY12 register bit field */
	union {
		volatile uint32_t STEPDELAY12;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY12_bit;
	}; // 0xc8

	/* SYS_ADC0_STEPCONFIG13 register bit field */
	union {
		volatile uint32_t STEPCONFIG13;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG13_bit;
	}; // 0xcc

	/* SYS_ADC0_STEPDELAY13 register bit field */
	union {
		volatile uint32_t STEPDELAY13;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY13_bit;
	}; // 0xd0

	/* SYS_ADC0_STEPCONFIG14 register bit field */
	union {
		volatile uint32_t STEPCONFIG14;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG14_bit;
	}; // 0xd4

	/* SYS_ADC0_STEPDELAY14 register bit field */
	union {
		volatile uint32_t STEPDELAY14;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY14_bit;
	}; // 0xd8

	/* SYS_ADC0_STEPCONFIG15 register bit field */
	union {
		volatile uint32_t STEPCONFIG15;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t XPPSW_SWC : 1; // 5
			uint32_t XNNSW_SWC : 1; // 6
			uint32_t YPPSW_SWC : 1; // 7
			uint32_t YNNSW_SWC : 1; // 8
			uint32_t XNPSW_SWC : 1; // 9
			uint32_t YPNSW_SWC : 1; // 10
			uint32_t WPNSW_SWC : 1; // 11
			uint32_t SEL_RFP__SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM__SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK : 1; // 27
			uint32_t rsvd28 : 4; // 31:28
		} STEPCONFIG15_bit;
	}; // 0xdc

	/* SYS_ADC0_STEPDELAY15 register bit field */
	union {
		volatile uint32_t STEPDELAY15;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY15_bit;
	}; // 0xe0

	/* SYS_ADC0_FIFOCOUNT0 register bit field */
	union {
		volatile uint32_t FIFOCOUNT0;

		volatile struct {
			uint32_t WORDS_IN_FIFO0 : 7; // 6:0
			uint32_t rsvd7 : 25; // 31:7
		} FIFOCOUNT0_bit;
	}; // 0xe4

	/* SYS_ADC0_FIFOTHR0 register bit field */
	union {
		volatile uint32_t FIFOTHR0;

		volatile struct {
			uint32_t FIFO0_THRESHOLD_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} FIFOTHR0_bit;
	}; // 0xe8

	/* SYS_ADC0_DMAREQ0 register bit field */
	union {
		volatile uint32_t DMAREQ0;

		volatile struct {
			uint32_t DMA_REQUEST_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} DMAREQ0_bit;
	}; // 0xec

	/* SYS_ADC0_FIFOCOUNT1 register bit field */
	union {
		volatile uint32_t FIFOCOUNT1;

		volatile struct {
			uint32_t WORDS_IN_FIFO0 : 7; // 6:0
			uint32_t rsvd7 : 25; // 31:7
		} FIFOCOUNT1_bit;
	}; // 0xf0

	/* SYS_ADC0_FIFOTHR1 register bit field */
	union {
		volatile uint32_t FIFOTHR1;

		volatile struct {
			uint32_t FIFO0_THRESHOLD_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} FIFOTHR1_bit;
	}; // 0xf4

	/* SYS_ADC0_DMAREQ1 register bit field */
	union {
		volatile uint32_t DMAREQ1;

		volatile struct {
			uint32_t DMA_REQUEST_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} DMAREQ1_bit;
	}; // 0xf8

	uint8_t rsvdfc[4]; // 0xfc - 0xff

	/* SYS_ADC0_FIFO0DATA register bit field */
	union {
		volatile uint32_t FIFO0DATA;

		volatile struct {
			uint32_t ADCDATA : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t ADCCHNLID : 4; // 19:16
			uint32_t rsvd20 : 12; // 31:20
		} FIFO0DATA_bit;
	}; // 0x100

	uint8_t rsvd104[252]; // 0x104 - 0x1ff

	/* SYS_ADC0_FIFO1DATA register bit field */
	union {
		volatile uint32_t FIFO1DATA;

		volatile struct {
			uint32_t ADCDATA : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t ADCCHNLID : 4; // 19:16
			uint32_t rsvd20 : 12; // 31:20
		} FIFO1DATA_bit;
	}; // 0x200

} sysAdc0TscSs;

/* Definition of ADC0 register structures. */
#define ADC0_TSC_SS (*((volatile sysAdc0TscSs*)0x44E0D000))

#endif /* _SYS_ADC0_H_ */
