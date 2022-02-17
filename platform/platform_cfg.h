#ifndef _PLATFORM_CFG_H_
#define _PLATFORM_CFG_H_

#include "sys_config.h"

#if SYS_EXECUTION_PLATFORM == BK7236_FPGA_PLATFORM
#include "bk7236_fpga.h"
#else
#error no platform
#endif

#define _RO_
#define _RW_
#endif
// eof

