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

#ifndef _SYS_MAILBOX_H_
#define _SYS_MAILBOX_H_

/* SYS_MAILBOX register set */
typedef struct {

	/* SYS_MAILBOX_REVISION register bit field */
	union {
		volatile uint32_t REVISION;

		volatile struct {
			unsigned REVISION	:32;	//31:0
		} REVISION_bit;
	};	// 0x0

	uint32_t rsvd4[3];		// 0x4 - 0xC

	/* SYS_MAILBOX_SYSCONFIG register bit field */
	union {
		volatile uint32_t SYSCONFIG;

		volatile struct {
			unsigned SOFTRESET	: 1;	//0
			unsigned rsvd1		: 1;	//1
			unsigned SLIDLEMODE : 2;	//3:2
			unsigned rsvd4		: 28;	//31:4
		} SYSCONFIG_bit;
	};	// 0x10

	uint32_t rsvd14[11];		// 0x14 - 0x3C

	/* SYS_MAILBOX_MESSAGE register bit fields */
	union {
		volatile uint32_t MESSAGE[12];

		volatile struct {
			unsigned MESSAGE : 32;		//31:0
		} MESSAGE_bit[12];
	};	// 0x40-0x6C

	uint32_t rsvd70[4];		// 0x70 - 0x7C

	/* SYS_MAILBOX_FIFOSTATUS register bit fields */
	union {
		volatile uint32_t FIFOSTATUS[12];

		volatile struct {
			unsigned FIFOFULL	: 1;		//0
			unsigned rsvd		: 31;		//31:1
		} FIFOSTATUS_bit[12];
	};	// 0x80-0xAC

	uint32_t rsvdB0[4];		// 0xB0 - 0xBC

	/* SYS_MAILBOX_MSGSTATUS register bit fields */
	union {
		volatile uint32_t MSGSTATUS[12];

		volatile struct {
			unsigned NBOFMSG : 3;		//2:0
			unsigned rsvd	 : 29;		//31:3
		} MSGSTATUS_bit[12];
	};	// 0xC0-EC

	uint32_t rsvdF0[4];		// 0xF0 - 0xFC

	volatile struct {
		union {
			volatile uint32_t STATUS_RAW;

			volatile struct {
				unsigned NEWMSGSTATUSMB0	: 1;		//0
				unsigned NOTFULLSTATUSMB0	: 1;		//1
				unsigned NEWMSGSTATUSMB1	: 1;		//2
				unsigned NOTFULLSTATUSMB1	: 1;		//3
				unsigned NEWMSGSTATUSMB2	: 1;		//4
				unsigned NOTFULLSTATUSMB2	: 1;		//5
				unsigned NEWMSGSTATUSMB3	: 1;		//6
				unsigned NOTFULLSTATUSMB3	: 1;		//7
				unsigned NEWMSGSTATUSMB4	: 1;		//8
				unsigned NOTFULLSTATUSMB4	: 1;		//9
				unsigned NEWMSGSTATUSMB5	: 1;		//10
				unsigned NOTFULLSTATUSMB5	: 1;		//11
				unsigned NEWMSGSTATUSMB6	: 1;		//12
				unsigned NOTFULLSTATUSMB6	: 1;		//13
				unsigned NEWMSGSTATUSMB7	: 1;		//14
				unsigned NOTFULLSTATUSMB7	: 1;		//15
				unsigned NEWMSGSTATUSMB8	: 1;		//16
				unsigned NOTFULLSTATUSMB8	: 1;		//17
				unsigned NEWMSGSTATUSMB9	: 1;		//18
				unsigned NOTFULLSTATUSMB9	: 1;		//19
				unsigned NEWMSGSTATUSMB10	: 1;		//20
				unsigned NOTFULLSTATUSMB10	: 1;		//21
				unsigned NEWMSGSTATUSMB11	: 1;		//22
				unsigned NOTFULLSTATUSMB11	: 1;		//23
				unsigned rsvd24				: 8;		//31:24
			} STATUS_RAW_bit;
		};
		union {
			volatile uint32_t STATUS_CLR;

			volatile struct {
				unsigned NEWMSGSTATUSMB0	: 1;		//0
				unsigned NOTFULLSTATUSMB0	: 1;		//1
				unsigned NEWMSGSTATUSMB1	: 1;		//2
				unsigned NOTFULLSTATUSMB1	: 1;		//3
				unsigned NEWMSGSTATUSMB2	: 1;		//4
				unsigned NOTFULLSTATUSMB2	: 1;		//5
				unsigned NEWMSGSTATUSMB3	: 1;		//6
				unsigned NOTFULLSTATUSMB3	: 1;		//7
				unsigned NEWMSGSTATUSMB4	: 1;		//8
				unsigned NOTFULLSTATUSMB4	: 1;		//9
				unsigned NEWMSGSTATUSMB5	: 1;		//10
				unsigned NOTFULLSTATUSMB5	: 1;		//11
				unsigned NEWMSGSTATUSMB6	: 1;		//12
				unsigned NOTFULLSTATUSMB6	: 1;		//13
				unsigned NEWMSGSTATUSMB7	: 1;		//14
				unsigned NOTFULLSTATUSMB7	: 1;		//15
				unsigned NEWMSGSTATUSMB8	: 1;		//16
				unsigned NOTFULLSTATUSMB8	: 1;		//17
				unsigned NEWMSGSTATUSMB9	: 1;		//18
				unsigned NOTFULLSTATUSMB9	: 1;		//19
				unsigned NEWMSGSTATUSMB10	: 1;		//20
				unsigned NOTFULLSTATUSMB10	: 1;		//21
				unsigned NEWMSGSTATUSMB11	: 1;		//22
				unsigned NOTFULLSTATUSMB11	: 1;		//23
				unsigned rsvd24				: 8;		//31:24
			} STATUS_CLR_bit;
		};
		union {
			volatile uint32_t ENABLE_SET;

			volatile struct {
				unsigned NEWMSGSTATUSMB0	: 1;		//0
				unsigned NOTFULLSTATUSMB0	: 1;		//1
				unsigned NEWMSGSTATUSMB1	: 1;		//2
				unsigned NOTFULLSTATUSMB1	: 1;		//3
				unsigned NEWMSGSTATUSMB2	: 1;		//4
				unsigned NOTFULLSTATUSMB2	: 1;		//5
				unsigned NEWMSGSTATUSMB3	: 1;		//6
				unsigned NOTFULLSTATUSMB3	: 1;		//7
				unsigned NEWMSGSTATUSMB4	: 1;		//8
				unsigned NOTFULLSTATUSMB4	: 1;		//9
				unsigned NEWMSGSTATUSMB5	: 1;		//10
				unsigned NOTFULLSTATUSMB5	: 1;		//11
				unsigned NEWMSGSTATUSMB6	: 1;		//12
				unsigned NOTFULLSTATUSMB6	: 1;		//13
				unsigned NEWMSGSTATUSMB7	: 1;		//14
				unsigned NOTFULLSTATUSMB7	: 1;		//15
				unsigned NEWMSGSTATUSMB8	: 1;		//16
				unsigned NOTFULLSTATUSMB8	: 1;		//17
				unsigned NEWMSGSTATUSMB9	: 1;		//18
				unsigned NOTFULLSTATUSMB9	: 1;		//19
				unsigned NEWMSGSTATUSMB10	: 1;		//20
				unsigned NOTFULLSTATUSMB10	: 1;		//21
				unsigned NEWMSGSTATUSMB11	: 1;		//22
				unsigned NOTFULLSTATUSMB11	: 1;		//23
				unsigned rsvd24				: 8;		//31:24
			} ENABLE_SET_bit;
		};
		union {
			volatile uint32_t ENABLE_CLR;

			volatile struct {
				unsigned NEWMSGSTATUSMB0	: 1;		//0
				unsigned NOTFULLSTATUSMB0	: 1;		//1
				unsigned NEWMSGSTATUSMB1	: 1;		//2
				unsigned NOTFULLSTATUSMB1	: 1;		//3
				unsigned NEWMSGSTATUSMB2	: 1;		//4
				unsigned NOTFULLSTATUSMB2	: 1;		//5
				unsigned NEWMSGSTATUSMB3	: 1;		//6
				unsigned NOTFULLSTATUSMB3	: 1;		//7
				unsigned NEWMSGSTATUSMB4	: 1;		//8
				unsigned NOTFULLSTATUSMB4	: 1;		//9
				unsigned NEWMSGSTATUSMB5	: 1;		//10
				unsigned NOTFULLSTATUSMB5	: 1;		//11
				unsigned NEWMSGSTATUSMB6	: 1;		//12
				unsigned NOTFULLSTATUSMB6	: 1;		//13
				unsigned NEWMSGSTATUSMB7	: 1;		//14
				unsigned NOTFULLSTATUSMB7	: 1;		//15
				unsigned NEWMSGSTATUSMB8	: 1;		//16
				unsigned NOTFULLSTATUSMB8	: 1;		//17
				unsigned NEWMSGSTATUSMB9	: 1;		//18
				unsigned NOTFULLSTATUSMB9	: 1;		//19
				unsigned NEWMSGSTATUSMB10	: 1;		//20
				unsigned NOTFULLSTATUSMB10	: 1;		//21
				unsigned NEWMSGSTATUSMB11	: 1;		//22
				unsigned NOTFULLSTATUSMB11	: 1;		//23
				unsigned rsvd24				: 8;		//31:24
			} ENABLE_CLR_bit;
		};
	} IRQ[4];

	/* SYS_MAILBOX_IRQ_EOI register bit fields */
	union {
		volatile uint32_t IRQ_EOI;

		volatile struct {
			unsigned EOIVAL	: 2;		//1:0
			unsigned rsvd2		: 30;		//31:2
		} IRQ_EOI_bit;
	};	// 0x140

} sysMailbox;

/* Definition of control register structures. */
#define MBX1 (*((volatile sysMailbox*)0x4A0F4000))
#define MBX2 (*((volatile sysMailbox*)0x4883A000))
#define MBX3 (*((volatile sysMailbox*)0x4883C000))
#define MBX4 (*((volatile sysMailbox*)0x4883E000))
#define MBX5 (*((volatile sysMailbox*)0x48840000))
#define MBX6 (*((volatile sysMailbox*)0x48842000))
#define MBX7 (*((volatile sysMailbox*)0x48844000))
#define MBX8 (*((volatile sysMailbox*)0x48846000))
#define MBX9 (*((volatile sysMailbox*)0x4885E000))
#define MBX10 (*((volatile sysMailbox*)0x48860000))
#define MBX11 (*((volatile sysMailbox*)0x48862000))
#define MBX12 (*((volatile sysMailbox*)0x48864000))
#define MBX13 (*((volatile sysMailbox*)0x48802000))

#endif /* _SYS_MAILBOX_H_ */
