#include "secure_uart.h"
#include "stdio.h"
#include "string.h"
#include <stdbool.h>          // standard boolean definitions
#include <stdarg.h>

void secure_uart_init(uint32_t baud_rate, uint8_t rx_fifo_thr)
{
    uint32_t baud_divisor;

	baud_divisor           = 25000000 / baud_rate;
    baud_divisor           = baud_divisor - 1;

    REG_APB3_UART_CFG      = (   (DEF_STOP_BIT    << sft_UART_CONF_STOP_LEN)
                                 | (DEF_PARITY_MODE << sft_UART_CONF_PAR_MODE)
                                 | (DEF_PARITY_EN   << sft_UART_CONF_PAR_EN)
                                 | (DEF_DATA_LEN    << sft_UART_CONF_UART_LEN)
                                 | (baud_divisor    << sft_UART_CONF_CLK_DIVID)
                                 | (DEF_IRDA_MODE   << sft_UART_CONF_IRDA)
                                 | (DEF_RX_EN       << sft_UART_CONF_RX_ENABLE)
                                 | (DEF_TX_EN       << sft_UART_CONF_TX_ENABLE));

    REG_APB3_UART_FIFO_THRESHOLD = ((rx_fifo_thr << sft_UART_FIFO_CONF_RX_FIFO)
                                    | (0x40 << sft_UART_FIFO_CONF_TX_FIFO));
    REG_APB3_UART_INT_ENABLE = 0;             /* Disable UART Interrupts */
}

int bk_secure_put_char(char *st)
{
    while (*st)
    {
        if(UART_TX_WRITE_READY)
        {
            REG_APB3_UART_DATA = *st;
            st++;
        }
    }

    return 1;
}

static char _bk_secure_printf_buff[128];
int bk_secure_printf(const char *fmt, ...)
{
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = vsnprintf(_bk_secure_printf_buff, sizeof(_bk_secure_printf_buff), fmt, ap);
    va_end(ap);
    bk_secure_put_char(_bk_secure_printf_buff);

    return n;
}
// eof

