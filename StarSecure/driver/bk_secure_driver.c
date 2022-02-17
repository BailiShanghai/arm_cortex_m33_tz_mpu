#include "bk_secure_driver.h"

void bk_secure_driver_init(void)
{
    secure_uart_init(115200, 16);
}

void bk_secure_driver_deinit(void)
{
}
// eof

