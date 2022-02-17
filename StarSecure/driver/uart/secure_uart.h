#ifndef _SECURE_UART_H_
#define _SECURE_UART_H_

#include "stdint.h"
#include "platform_cfg.h"

#define DEF_TX_EN                   0x1
#define DEF_RX_EN                   0x1
#define DEF_IRDA_MODE               0x0    // 0:uart mode  1:IRDA MODE
#define DEF_DATA_LEN                0x3  // 0=5bit, 1=6bit, 2=7bit, 3=8bit
#define DEF_PARITY_EN               0x0  // 0=no parity  1: enable parity
#define DEF_PARITY_MODE             0x0  // 0:odd  1: even
#define DEF_STOP_BIT                0x1  // 1bit

extern void secure_uart_init(uint32_t baud_rate, uint8_t rx_fifo_thr);
extern int bk_secure_printf(const char *fmt, ...);
#endif

///End of file
