/**************************************************************************//**
 * @file     Lowlevel_Retarget.h
 * @brief    Header file: CMSIS ArmChina STAR low level retarget interface with standard IO, peripherals
 * @version  V1.0.0
 * @date     10. March 2021
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

extern int stdout_putchar (int ch);
extern int stdin_getchar (void);
extern void UartStdOutInit(void);


