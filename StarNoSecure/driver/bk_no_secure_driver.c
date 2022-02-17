#include "bk_no_secure_driver.h"

void bk_no_secure_driver_init(void)
{
    no_secure_uart_init(115200, 16);
}

void bk_no_secure_driver_deinit(void)
{
}
// eof

