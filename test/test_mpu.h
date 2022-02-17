#ifndef _TEST_MPU_H_
#define _TEST_MPU_H_

#define MPU_TYPE (*(volatile unsigned long*)(0xE000ED90UL))  
#define MPU_CTRL (*(volatile unsigned long*)(0xE000ED94UL)) 
#define MPU_RNR (*(volatile unsigned long*)(0xE000ED98UL))
#define MPU_RBAR (*(volatile unsigned long*)(0xE000ED9CUL))
#define MPU_RLAR (*(volatile unsigned long*)(0xE000EDA0UL))
#define MPU_RBAR_A (*(volatile unsigned long*)(0xE000EDA4UL))
#define MPU_RLAR_A (*(volatile unsigned long*)(0xE000EDA8UL))
#define MPU_MAIR0 (*(volatile unsigned long*)(0xE000EDC0UL))
#define MPU_MAIR1 (*(volatile unsigned long*)(0xE000EDC4UL))
 
#endif // _TEST_MPU_H_
// eof
