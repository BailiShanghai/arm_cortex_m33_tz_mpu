/******************************************************************************
 * @file     startup_STAR.c
 * @brief    CMSIS Core Device Startup File for ArmChina-STAR Device
 * @version  V1.0.0
 * @date     24. April 2020
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited.
 * Copyright (c) 2019-2020 ArmChina.
 * All rights reserved.
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

#ifndef _STARTUP_STAR_H_
#define _STARTUP_STAR_H_

#include "secure_uart.h"

#define SS_PRINTF   bk_secure_printf

extern void Reset_Handler(void);
extern void Default_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SecureFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void Interrupt0_Handler(void);
extern void Interrupt1_Handler(void);
extern void Interrupt2_Handler(void);
extern void Interrupt3_Handler(void);
extern void Interrupt4_Handler(void);
extern void Interrupt5_Handler(void);
extern void Interrupt6_Handler(void);
extern void Interrupt7_Handler(void);
extern void Interrupt8_Handler(void);
extern void Interrupt9_Handler(void);
#endif // _STARTUP_STAR_H_
// eof

