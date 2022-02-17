#ifndef _BK7236_FPGA_H_
#define _BK7236_FPGA_H_

#define TE200_BASE                  0x70000000  // Security TE200 apb base addr
#define TE200_NS_BASE               0x70100000  // Non-Security TE200 apb base addr

#define BK7236_UART_BASE_ADDR       0x70200000

#define REG_APB3_UART_CFG                   (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x00*4)))
#define REG_APB3_UART_FIFO_THRESHOLD        (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x01*4)))
#define REG_APB3_UART_FIFO_STATUS           (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x02*4)))
#define REG_APB3_UART_DATA                  (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x03*4)))
#define REG_APB3_UART_INT_ENABLE            (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x04*4)))
#define REG_APB3_UART_INT_FLAG              (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x05*4)))
#define REG_APB3_UART_FC_CFG                (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x06*4)))
#define REG_APB3_UART_WAKEUP_ENABLE         (*((volatile unsigned long *)(BK7236_UART_BASE_ADDR+0x07*4)))

#define UART_TX_FIFO_SIZE       128
#define UART_RX_FIFO_SIZE       128
#define UART_TX_FIFO_COUNT      (REG_APB3_UART_FIFO_STATUS&0xff)
#define UART_RX_FIFO_COUNT      ((REG_APB3_UART_FIFO_STATUS>>8)&0xff)
#define UART_TX_FIFO_FULL        (REG_APB3_UART_FIFO_STATUS&0x00010000)
#define UART_TX_FIFO_EMPTY       (REG_APB3_UART_FIFO_STATUS&0x00020000)
#define UART_RX_FIFO_FULL        (REG_APB3_UART_FIFO_STATUS&0x00040000)
#define UART_RX_FIFO_EMPTY       (REG_APB3_UART_FIFO_STATUS&0x00080000)
#define UART_TX_WRITE_READY      (REG_APB3_UART_FIFO_STATUS&0x00100000)
#define UART_RX_READ_READY       (REG_APB3_UART_FIFO_STATUS&0x00200000)


#define sft_UART_CONF_TX_ENABLE          0
#define sft_UART_CONF_RX_ENABLE          1
#define sft_UART_CONF_IRDA               2
#define sft_UART_CONF_UART_LEN           3
#define sft_UART_CONF_PAR_EN             5
#define sft_UART_CONF_PAR_MODE           6
#define sft_UART_CONF_STOP_LEN           7
#define sft_UART_CONF_CLK_DIVID          8

#define sft_UART_FIFO_CONF_TX_FIFO       0
#define sft_UART_FIFO_CONF_RX_FIFO       8
#define sft_UART_FIFO_CONF_DETECT_TIME   16

#define bit_UART_INT_TX_NEED_WRITE       ( 1 << 0 )
#define bit_UART_INT_RX_NEED_READ        ( 1 << 1 )
#define bit_UART_INT_RX_OVER_FLOW        ( 1 << 2 )
#define bit_UART_INT_RX_PAR_ERR          ( 1 << 3 )
#define bit_UART_INT_RX_STOP_ERR         ( 1 << 4 )
#define bit_UART_INT_TX_STOP_END         ( 1 << 5 )
#define bit_UART_INT_RX_STOP_END         ( 1 << 6 )
#define bit_UART_INT_RXD_WAKEUP          ( 1 << 7 )
#endif
// eof

