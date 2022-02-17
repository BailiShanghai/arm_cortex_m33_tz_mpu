#include <stdio.h>
#include <stdarg.h>

char buf[1024];

void tz_put_char_int(void)
{
    (*(volatile unsigned long *)(0x40000400UL)) = 0xFFFF;
}

void tz_put_char(unsigned char value)
{
#define GPIO_00_OUTPUT (*(volatile unsigned long*)(0x40000000UL))
    unsigned int tmp = (value & 0x7F) << 8;

    GPIO_00_OUTPUT = tmp;

    tmp |= 1 << 15;
    GPIO_00_OUTPUT = tmp;

    GPIO_00_OUTPUT = tmp & 0x7FFFF;
}

unsigned int tz_printf(const char *fmt, ...)
{
    unsigned int count, i;

    va_list args;
    va_start(args, fmt);
    count = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    for (i = 0; i < count; i++)
    {
        tz_put_char(buf[i]);
    }

    return count;
}