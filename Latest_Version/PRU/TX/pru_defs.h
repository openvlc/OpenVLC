
#ifndef _PRU_DEFS_
#define _PRU_DEFS_

/* Constants */

#define SE_PRU0_TO_ARM			16
#define SE_ARM_TO_PRU0			17
#define SE_PRU1_TO_PRU0			18

#define HOST1_INT			((uint32_t) 1<<31)
#define HOST0_INT			((uint32_t) 1<<30)

#define R31_VECTOR_VALID_STROBE_BIT	5
#define R31_PRU1_TO_PRU0		(SE_PRU1_TO_PRU0 - 16)

#define RPMSG_CHAN_NAME			"rpmsg-pru"

#define PRU0_RPMSG_CHAN_DESC		"Channel 30"
#define PRU0_RPMSG_CHAN_PORT		30
#define PRU1_RPMSG_CHAN_DESC		"Channel 31"
#define PRU1_RPMSG_CHAN_PORT		31

#define VIRTIO_CONFIG_S_DRIVER_OK	4

/* Macros */

#define check_host_int(host)\
			(__R31 & host)

#define generate_sys_eve(sys_eve)\
			__R31 = ( (1 << R31_VECTOR_VALID_STROBE_BIT) | (SE_PRU1_TO_PRU0-16))

#endif
