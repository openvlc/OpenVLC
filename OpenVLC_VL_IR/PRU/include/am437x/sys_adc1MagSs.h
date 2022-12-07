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

#ifndef _SYS_ADC1_H_
#define _SYS_ADC1_H_

/* SYS ADC1 register set */
typedef struct {

	/* SYS_ADC1_REVISION register bit field */
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

	/* SYS_ADC1_SYSCONFIG register bit field */
	union {
		volatile uint32_t SYSCONFIG;

		volatile struct {
			uint32_t rsvd0 : 2; // 1:0
			uint32_t IDLEMODE : 2; // 3:2
			uint32_t rsvd4 : 28; // 31:4
		} SYSCONFIG_bit;
	}; // 0x10

	uint8_t rsvd14[16]; // 0x14 - 0x23

	/* SYS_ADC1_IRQSTS_RAW register bit field */
	union {
		volatile uint32_t IRQSTS_RAW;

		volatile struct {
			uint32_t rsvd0 : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t START_OF_SWIPE : 1; // 9
			uint32_t rsvd10 : 22; // 31:10
		} IRQSTS_RAW_bit;
	}; // 0x24

	/* SYS_ADC1_IRQSTS register bit field */
	union {
		volatile uint32_t IRQSTS;

		volatile struct {
			uint32_t rsvd0 : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t START_OF_SWIPE : 1; // 9
			uint32_t rsvd10 : 22; // 31:10
		} IRQSTS_bit;
	}; // 0x28

	/* SYS_ADC1_IRQEN_SET register bit field */
	union {
		volatile uint32_t IRQEN_SET;

		volatile struct {
			uint32_t rsvd0 : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t START_OF_SWIPE : 1; // 9
			uint32_t rsvd10 : 22; // 31:10
		} IRQEN_SET_bit;
	}; // 0x2c

	/* SYS_ADC1_IRQEN_CLR register bit field */
	union {
		volatile uint32_t IRQEN_CLR;

		volatile struct {
			uint32_t rsvd0 : 1; // 0
			uint32_t END_OF_SEQUENCE : 1; // 1
			uint32_t FIFO0_THRESHOLD : 1; // 2
			uint32_t FIFO0_OVERRUN : 1; // 3
			uint32_t FIFO0_UNDERFLOW : 1; // 4
			uint32_t FIFO1_THRESHOLD : 1; // 5
			uint32_t FIFO1_OVERRUN : 1; // 6
			uint32_t FIFO1_UNDERFLOW : 1; // 7
			uint32_t OUT_OF_RANGE : 1; // 8
			uint32_t START_OF_SWIPE : 1; // 9
			uint32_t rsvd10 : 22; // 31:10
		} IRQEN_CLR_bit;
	}; // 0x30

	uint8_t rsvd34[4]; // 0x34 - 0x37

	/* SYS_ADC1_DMAEN_SET register bit field */
	union {
		volatile uint32_t DMAEN_SET;

		volatile struct {
			uint32_t ENABLE0 : 1; // 0
			uint32_t ENABLE1 : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} DMAEN_SET_bit;
	}; // 0x38

	/* SYS_ADC1_DMAEN_CLR register bit field */
	union {
		volatile uint32_t DMAEN_CLR;

		volatile struct {
			uint32_t ENABLE0 : 1; // 0
			uint32_t ENABLE1 : 1; // 1
			uint32_t rsvd2 : 30; // 31:2
		} DMAEN_CLR_bit;
	}; // 0x3c

	/* SYS_ADC1_CTRL register bit field */
	union {
		volatile uint32_t CTRL;

		volatile struct {
			uint32_t ADC1_ENABLE : 1; // 0
			uint32_t STEP_ID_TAG : 1; // 1
			uint32_t SIMULTANEOUS_CONTROL : 1; // 2
			uint32_t rsvd3 : 1; // 3
			uint32_t ADC_POWER_DOWN : 1; // 4
			uint32_t PREAMP_PD : 1; // 5
			uint32_t PREAMP_BYPASS : 1; // 6
			uint32_t rsvd7 : 1; // 7
			uint32_t HW_EVENT_MAPPING : 1; // 8
			uint32_t rsvd9 : 23; // 31:9
		} CTRL_bit;
	}; // 0x40

	/* SYS_ADC1_ADCSTAT register bit field */
	union {
		volatile uint32_t ADCSTAT;

		volatile struct {
			uint32_t STEP_ID : 5; // 4:0
			uint32_t FSM_BUSY : 1; // 5
			uint32_t rsvd6 : 26; // 31:6
		} ADCSTAT_bit;
	}; // 0x44

	/* SYS_ADC1_ADCRANGE register bit field */
	union {
		volatile uint32_t ADCRANGE;

		volatile struct {
			uint32_t THRESHOLD_LOW_RANGE_DATA : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t THRESHOLD_HIGH_RANGE_DATA : 12; // 27:16
			uint32_t rsvd28 : 4; // 31:28
		} ADCRANGE_bit;
	}; // 0x48

	/* SYS_ADC1_CLKDIV register bit field */
	union {
		volatile uint32_t CLKDIV;

		volatile struct {
			uint32_t ADC_CLKDIV : 16; // 15:0
			uint32_t rsvd16 : 16; // 31:16
		} CLKDIV_bit;
	}; // 0x4c

	uint8_t rsvd50[4]; // 0x50 - 0x53

	/* SYS_ADC1_STEPEN register bit field */
	union {
		volatile uint32_t STEPEN;

		volatile struct {
			uint32_t rsvd0 : 1; // 0
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

	/* SYS_ADC1_IDLECONFIG register bit field */
	union {
		volatile uint32_t IDLECONFIG;

		volatile struct {
			uint32_t rsvd0 : 5; // 4:0
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t rsvd11 : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t rsvd26 : 2; // 27:26
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t rsvd30 : 2; // 31:30
		} IDLECONFIG_bit;
	}; // 0x58

	/* SYS_ADC1_SWIPE_COMPARE_REG1_2 register bit field */
	union {
		volatile uint32_t SWIPE_COMPARE_REG1_2;

		volatile struct {
			uint32_t THRESHOLD_DATA2 : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t THRESHOLD_DATA1 : 12; // 27:16
			uint32_t rsvd28 : 4; // 31:28
		} SWIPE_COMPARE_REG1_2_bit;
	}; // 0x5c

	/* SYS_ADC1_SWIPE_COMPARE_REG3_4 register bit field */
	union {
		volatile uint32_t SWIPE_COMPARE_REG3_4;

		volatile struct {
			uint32_t THRESHOLD_DATA4 : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t THRESHOLD_DATA3 : 12; // 27:16
			uint32_t rsvd28 : 4; // 31:28
		} SWIPE_COMPARE_REG3_4_bit;
	}; // 0x60

	/* SYS_ADC1_STEPCONFIG1 register bit field */
	union {
		volatile uint32_t STEPCONFIG1;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG1_bit;
	}; // 0x64

	/* SYS_ADC1_STEPDELAY1 register bit field */
	union {
		volatile uint32_t STEPDELAY1;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY1_bit;
	}; // 0x68

	/* SYS_ADC1_STEPCONFIG2 register bit field */
	union {
		volatile uint32_t STEPCONFIG2;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG2_bit;
	}; // 0x6c

	/* SYS_ADC1_STEPDELAY2 register bit field */
	union {
		volatile uint32_t STEPDELAY2;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY2_bit;
	}; // 0x70

	/* SYS_ADC1_STEPCONFIG3 register bit field */
	union {
		volatile uint32_t STEPCONFIG3;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG3_bit;
	}; // 0x74

	/* SYS_ADC1_STEPDELAY3 register bit field */
	union {
		volatile uint32_t STEPDELAY3;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY3_bit;
	}; // 0x78

	/* SYS_ADC1_STEPCONFIG4 register bit field */
	union {
		volatile uint32_t STEPCONFIG4;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG4_bit;
	}; // 0x7c

	/* SYS_ADC1_STEPDELAY4 register bit field */
	union {
		volatile uint32_t STEPDELAY4;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY4_bit;
	}; // 0x80

	/* SYS_ADC1_STEPCONFIG5 register bit field */
	union {
		volatile uint32_t STEPCONFIG5;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG5_bit;
	}; // 0x84

	/* SYS_ADC1_STEPDELAY5 register bit field */
	union {
		volatile uint32_t STEPDELAY5;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY5_bit;
	}; // 0x88

	/* SYS_ADC1_STEPCONFIG6 register bit field */
	union {
		volatile uint32_t STEPCONFIG6;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG6_bit;
	}; // 0x8c

	/* SYS_ADC1_STEPDELAY6 register bit field */
	union {
		volatile uint32_t STEPDELAY6;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY6_bit;
	}; // 0x90

	/* SYS_ADC1_STEPCONFIG7 register bit field */
	union {
		volatile uint32_t STEPCONFIG7;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG7_bit;
	}; // 0x94

	/* SYS_ADC1_STEPDELAY7 register bit field */
	union {
		volatile uint32_t STEPDELAY7;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY7_bit;
	}; // 0x98

	/* SYS_ADC1_STEPCONFIG8 register bit field */
	union {
		volatile uint32_t STEPCONFIG8;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG8_bit;
	}; // 0x9c

	/* SYS_ADC1_STEPDELAY8 register bit field */
	union {
		volatile uint32_t STEPDELAY8;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY8_bit;
	}; // 0xa0

	/* SYS_ADC1_STEPCONFIG9 register bit field */
	union {
		volatile uint32_t STEPCONFIG9;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG9_bit;
	}; // 0xa4

	/* SYS_ADC1_STEPDELAY9 register bit field */
	union {
		volatile uint32_t STEPDELAY9;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY9_bit;
	}; // 0xa8

	/* SYS_ADC1_STEPCONFIG10 register bit field */
	union {
		volatile uint32_t STEPCONFIG10;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG10_bit;
	}; // 0xac

	/* SYS_ADC1_STEPDELAY10 register bit field */
	union {
		volatile uint32_t STEPDELAY10;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY10_bit;
	}; // 0xb0

	/* SYS_ADC1_STEPCONFIG11 register bit field */
	union {
		volatile uint32_t STEPCONFIG11;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG11_bit;
	}; // 0xb4

	/* SYS_ADC1_STEPDELAY11 register bit field */
	union {
		volatile uint32_t STEPDELAY11;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY11_bit;
	}; // 0xb8

	/* SYS_ADC1_STEPCONFIG12 register bit field */
	union {
		volatile uint32_t STEPCONFIG12;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG12_bit;
	}; // 0xbc

	/* SYS_ADC1_STEPDELAY12 register bit field */
	union {
		volatile uint32_t STEPDELAY12;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY12_bit;
	}; // 0xc0

	/* SYS_ADC1_STEPCONFIG13 register bit field */
	union {
		volatile uint32_t STEPCONFIG13;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG13_bit;
	}; // 0xc4

	/* SYS_ADC1_STEPDELAY13 register bit field */
	union {
		volatile uint32_t STEPDELAY13;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY13_bit;
	}; // 0xc8

	/* SYS_ADC1_STEPCONFIG14 register bit field */
	union {
		volatile uint32_t STEPCONFIG14;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG14_bit;
	}; // 0xcc

	/* SYS_ADC1_STEPDELAY14 register bit field */
	union {
		volatile uint32_t STEPDELAY14;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY14_bit;
	}; // 0xd0

	/* SYS_ADC1_STEPCONFIG15 register bit field */
	union {
		volatile uint32_t STEPCONFIG15;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG15_bit;
	}; // 0xd4

	/* SYS_ADC1_STEPDELAY15 register bit field */
	union {
		volatile uint32_t STEPDELAY15;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY15_bit;
	}; // 0xd8

	/* SYS_ADC1_STEPCONFIG16 register bit field */
	union {
		volatile uint32_t STEPCONFIG16;

		volatile struct {
			uint32_t MODE : 2; // 1:0
			uint32_t AVERAGING : 3; // 4:2
			uint32_t GAIN_CONTROL1 : 2; // 6:5
			uint32_t GAIN_CONTROL2 : 2; // 8:7
			uint32_t GAIN_CONTROL3 : 2; // 10:9
			uint32_t SWIPE_THRESHOLD_COMPARE_FEATURE : 1; // 11
			uint32_t SEL_RFP_SWC_2_0 : 3; // 14:12
			uint32_t SEL_INM_SWM_3_0 : 4; // 18:15
			uint32_t SEL_INP_SWC_3_0 : 4; // 22:19
			uint32_t SEL_RFM_SWC_1_0 : 2; // 24:23
			uint32_t DIFF_CNTRL : 1; // 25
			uint32_t FIFO_SELECT : 1; // 26
			uint32_t RANGE_CHECK_INTERRUPT : 1; // 27
			uint32_t GAIN_CONTROL4 : 2; // 29:28
			uint32_t SWIPE_THRESHOLD_REGISTER_POINTER : 2; // 31:30
		} STEPCONFIG16_bit;
	}; // 0xdc

	/* SYS_ADC1_STEPDELAY16 register bit field */
	union {
		volatile uint32_t STEPDELAY16;

		volatile struct {
			uint32_t OPENDELAY : 18; // 17:0
			uint32_t rsvd18 : 6; // 23:18
			uint32_t SAMPLEDELAY : 8; // 31:24
		} STEPDELAY16_bit;
	}; // 0xe0

	/* SYS_ADC1_FIFO0COUNT register bit field */
	union {
		volatile uint32_t FIFO0COUNT;

		volatile struct {
			uint32_t WORDS_IN_FIFO0 : 7; // 6:0
			uint32_t rsvd7 : 25; // 31:7
		} FIFO0COUNT_bit;
	}; // 0xe4

	/* SYS_ADC1_FIFO0THR register bit field */
	union {
		volatile uint32_t FIFO0THR;

		volatile struct {
			uint32_t FIFO0_THRESHOLD_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} FIFO0THR_bit;
	}; // 0xe8

	/* SYS_ADC1_DMA0REQ register bit field */
	union {
		volatile uint32_t DMA0REQ;

		volatile struct {
			uint32_t DMA_REQUEST_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} DMA0REQ_bit;
	}; // 0xec

	/* SYS_ADC1_FIFO1COUNT register bit field */
	union {
		volatile uint32_t FIFO1COUNT;

		volatile struct {
			uint32_t WORDS_IN_FIFO1 : 7; // 6:0
			uint32_t rsvd7 : 25; // 31:7
		} FIFO1COUNT_bit;
	}; // 0xf0

	/* SYS_ADC1_FIFO1THR register bit field */
	union {
		volatile uint32_t FIFO1THR;

		volatile struct {
			uint32_t FIFO1_THRESHOLD_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} FIFO1THR_bit;
	}; // 0xf4

	/* SYS_ADC1_DMA1REQ register bit field */
	union {
		volatile uint32_t DMA1REQ;

		volatile struct {
			uint32_t DMA_REQUEST_LEVEL : 6; // 5:0
			uint32_t rsvd6 : 26; // 31:6
		} DMA1REQ_bit;
	}; // 0xf8

	uint8_t rsvdfc[4]; // 0xfc - 0xff

	/* SYS_ADC1_FIFO0DATA register bit field */
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

	/* SYS_ADC1_FIFO1DATA register bit field */
	union {
		volatile uint32_t FIFO1DATA;

		volatile struct {
			uint32_t ADCDATA : 12; // 11:0
			uint32_t rsvd12 : 4; // 15:12
			uint32_t ADCCHNLID : 4; // 19:16
			uint32_t rsvd20 : 12; // 31:20
		} FIFO1DATA_bit;
	}; // 0x200

} sysAdc1MagSs;

/* Definition of ADC1 register structures. */
#define ADC1_MAG_SS (*((volatile sysAdc1MagSs*)0x4834C000))

#endif /* _SYS_ADC1_H_ */
