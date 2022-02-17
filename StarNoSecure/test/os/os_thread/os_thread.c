/**
 ******************************************************************************
 * @file    os_thread.c
 * @author
 * @version V1.0.0
 * @date
 * @brief   RTOS thread control demo.
 ******************************************************************************
 *
 *  The MIT License
 *  Copyright (c) 2017 Beken Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is furnished
 *  to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************
 */
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "os_thread.h"
#include "portmacro.h"

typedef void           *beken_thread_arg_t;
typedef void           *beken_thread_t;
#define os_printf      bk_no_secure_printf

BaseType_t rtos_thread_join(beken_thread_t *thread)
{
    return kNoErr;
}

void thread_0( beken_thread_arg_t arg )
{
    (void)( arg );

    os_printf( "This is thread 0\r\n");
    while ( 1 )
    {
        vTaskDelay((TickType_t)1000 );
        os_printf( "thread0_is_running\r\n");
    }

    /* Make with terminate state and IDLE thread will clean resources */
    vTaskDelete(NULL);
}

void thread_1( beken_thread_arg_t arg )
{
    (void)( arg );
    BaseType_t err = kNoErr;
    TaskHandle_t t_handler = NULL;

    /* Create a new thread, and this thread will delete its self and clean its resource */
    err = xTaskCreate( thread_0,
                       "Thread0",
                       0x400,
                       0,
                       5,
                       &t_handler);
    if(err != pdPASS)
    {
        os_printf("ERROR: Unable to start the thread 1.\r\n" );
    }

    while ( 1 )
    {
        os_printf( "thread1_is_running\r\n");
        vTaskDelay((TickType_t)1000 );
    }
}

void thread_2( beken_thread_arg_t arg )
{
    (void)( arg );

    while ( 1 )
    {
        os_printf( "This is thread 2\r\n" );
        vTaskDelay((TickType_t)600);
    }
}

/***************************************************************
   This function make two thread for Os_thread application.
***************************************************************/
int demo_start( void )
{
    BaseType_t err = kNoErr;
    TaskHandle_t t_handler1 = NULL, t_handler2 = NULL;

    os_printf("\r\n\r\noperating system thread demo............\r\n" );

    err = xTaskCreate( thread_1, "Thread1",
                       0x400,
                       0,
                       6,
                       &t_handler1);
    if(err != pdPASS)
    {
        os_printf("ERROR: Unable to start the thread 1.\r\n" );
        goto exit;
    }

    err = xTaskCreate( thread_2, "thread_2",
                       0x400,
                       0,
                       6,
                       &t_handler2);
    if(err != pdPASS)
    {
        os_printf("ERROR: Unable to start the thread 2.\r\n" );
        goto exit;
    }

exit:
    if ( err != pdPASS )
    {
        os_printf( "Thread exit with err: %d", err );

        if(t_handler1 != NULL)
        {
            vTaskDelete(t_handler1);
        }

        if(t_handler2 != NULL)
        {
            vTaskDelete(t_handler2);
        }
    }

    return err;
}
// eof

