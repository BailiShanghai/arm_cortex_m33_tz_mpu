/**************************************************************************//**
 * @file     main.c
 * @brief    main file of the coremark example.
 *           invoke core_main to run the benchmark testing.
 *           use system tick to count the cycles.
 * @version  V1.0.0
 * @date     29. June 2021
 ******************************************************************************/
/*
 * Copyright (c) 2018-2021 ArmChina. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "lowlevel_retarget.h"
#include "UART_APB.h"
#include "coremark.h"

#include <arm_cmse.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#if defined (STAR_CU)
#include "STAR_CU.h"
#elif defined (STAR_SP)
#include "STAR_SP.h"
#elif defined (STAR_SE)
#include "STAR_SE.h"
#endif

#include "platform_generic.h"
#include "bk_secure_driver.h"

/***********************************Macro Definition********************************************/
#define CLKB_MSK                            2UL
#define INTB_MSK                            1UL
#define ENAB_MSK                            0UL
#define NVIC_SYSTICK_CTRL                   ((volatile unsigned int *) 0xE000E010)
#define NVIC_SYSTICK_LOAD                   ((volatile unsigned int *) 0xE000E014)
#define NVIC_SYSTICK_CURRENT_VALUE          ((volatile unsigned int *) 0xE000E018)
#define NVIC_SYSTICK_CLK                    (1UL << CLKB_MSK)
#define NVIC_SYSTICK_INT                    (1UL << INTB_MSK)
#define NVIC_SYSTICK_ENABLE                 (1UL << ENAB_MSK)

#define TICK_FREQ                            1000      /*TickFreq	is 1000 times per second*/
#define SYSTEM_CLOCK                         20000000  /*SYSTEM_CLOCK must be replaced with the actual CPU clock*/

extern void gpio_set(unsigned long value);

/***********************************Function Definition*******************************************/
/*Setup SystemTick with defined SystemFreq and TickFreq
** Note that: SYSTEM_CLOCK must be the actual CPU clcok frequency on the platform you are using**
*/
void SetUp_SysTick(void)
{
    /*Stop and reset the SysTick*/
    *( NVIC_SYSTICK_CTRL ) = 0UL;
    *( NVIC_SYSTICK_CURRENT_VALUE ) = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    *( NVIC_SYSTICK_LOAD ) = ( SYSTEM_CLOCK / TICK_FREQ ) - 1UL;
    *( NVIC_SYSTICK_CTRL ) = NVIC_SYSTICK_CLK | NVIC_SYSTICK_INT | NVIC_SYSTICK_ENABLE;
}

/*definition of SysTickCounter for Time calculation*/
volatile ee_u32 SysTickCounter = 0;

/*SysTick_Handler used for time calculation
*/
void SysTick_Handler(void)
{
    SysTickCounter ++;
}

/* main function: to setup Systick and run CoreMark tests
** Round 1: Caches enabled by default **
** Round 2: Caches disabled in the main() **
*/
MAIN_RETURN_TYPE coremark_main(int argc, char *argv[]);

extern unsigned int tz_printf(const char *fmt, ...);


typedef void (*funcptr_void) (void) __attribute__((cmse_nonsecure_call));

#ifndef TZ_START_NS
#define TZ_START_NS (0x100000U)
#endif

volatile unsigned int secure_var __attribute__((section(".ARM.__at_0x20020000"))) = 0x1234;

extern void jump_to_no_secure(void);

void non_secure_re(void)
{
    funcptr_void NonSecure_ResetHandler;

    /* Add user setup code for secure part here*/

    /* Set non-secure main stack (MSP_NS) */
    __TZ_set_MSP_NS(*((uint32_t *)(TZ_START_NS)));

    /* Get non-secure reset handler */
    NonSecure_ResetHandler = (funcptr_void)(*((uint32_t *)((TZ_START_NS) + 4U)));

    /* Start non-secure state software application */
    NonSecure_ResetHandler();
}

void xn_f_test(void);
void xo_f_test(void);
void ro_f_test(void);
void mpu_setup(void);
void sfv_verify(void);

/* FreeRTOS includes. */
#include "secure_port_macros.h"

/* Start address of non-secure application. */
#define mainNONSECURE_APP_START_ADDRESS		( 0x00100000U )

/* typedef for non-secure Reset Handler. */
typedef void ( *NonSecureResetHandler_t )	( void ) __attribute__( ( cmse_nonsecure_call ) );
/*-----------------------------------------------------------*/

/* Boot into the non-secure code. */
void BootNonSecure( uint32_t ulNonSecureStartAddress );
/*-----------------------------------------------------------*/

int main(void)
{
	uint32_t i;
	uint32_t LED23 = 0;

	#if CONFIG_ENABLE_CM_BACKTRACE
	cm_backtrace_init("0.1", "0.1", "0.1");
	#endif

	#if CONFIG_ENABLE_MEMORY_PROTECTION_UNIT
	mpu_setup();
	#endif
	
	/* Add user setup code for secure part here*/
	unsigned int *p = (unsigned int *)0x20020000;
	(*(volatile unsigned long *)(0x40000400UL)) = 0x0c; // '1' is output enable
	(*(volatile unsigned long *)(0x40000000UL)) = 0x0c; //
	bk_secure_driver_init();

	bk_secure_printf("ARMSTAR Secure  a Build  st @ %s %s \r\n", __TIME__, __DATE__);
	bk_secure_printf("Secure World Start!\r\n");
	bk_secure_printf("Secure Value: %p, %x\r\n", &secure_var, secure_var);

	bk_secure_printf("xn_f_test function_pointer: %p\r\n", xn_f_test);
	bk_secure_printf("xo_f_test function_pointer: %p\r\n", xo_f_test);
	bk_secure_printf("ro_f_test function_pointer: %p\r\n", ro_f_test);
	
	PF_ASSERT(secure_var);

	#if CONFIG_ENABLE_SECURITY_FIELD_VERIFY
	sfv_verify();
	#endif

	/* Boot the non-secure code. */
	BootNonSecure( mainNONSECURE_APP_START_ADDRESS );
	
	/* Non-secure software does not return, this code is not executed */
	while (1)
	{
		//bk_secure_printf("Secure\r\n");
		__NOP();
	}
}

void BootNonSecure( uint32_t ulNonSecureStartAddress )
{
	NonSecureResetHandler_t pxNonSecureResetHandler;

	/* Main Stack Pointer value for the non-secure side is the first entry in
	 * the non-secure vector table. Read the first entry and assign the same to
	 * the non-secure main stack pointer(MSP_NS). */
	secureportSET_MSP_NS( *( ( uint32_t * )( ulNonSecureStartAddress ) ) );

	/* Non secure Reset Handler is the second entry in the non-secure vector
	 * table. Read the non-secure reset handler.
	 */
	pxNonSecureResetHandler = ( NonSecureResetHandler_t )( * ( ( uint32_t * ) ( ( ulNonSecureStartAddress ) + 4U ) ) );

	/* Start non-secure software application by jumping to the non-secure Reset
	 * Handler. */
	pxNonSecureResetHandler();
}
// eof
