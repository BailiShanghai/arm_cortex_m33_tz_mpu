#include "platform_cfg.h"
#include "mpu_armstar_m33.h"
#include "mpu_config.h"

int bk_secure_printf(const char *fmt, ...);

uint32_t mpu_get_type(void)
{
	uint32_t region_num;
	uint32_t mpu_info;

	mpu_info = MPU->TYPE;

	region_num = (mpu_info & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos;
	bk_secure_printf("\r\n[MPU]\r\n[MPU Capability]The supported data regions number:%d\r\n", region_num);
	if(mpu_info & MPU_TYPE_SEPARATE_Msk){
		bk_secure_printf("[MPU Capability]Support for SEPARATE instructions and data address regions\r\n");
	}else{
		bk_secure_printf("[MPU Capability]Support for UNIFIED instructions and data address regions\r\n");
	}

	return region_num;
}

#if CONFIG_MPU_DEMO
int mpu_config_demo(void) 
{
	// Set Region 0 using Attr 0
	ARM_MPU_SetMemAttr(0UL, ARM_MPU_ATTR(       /* Normal memory */
		ARM_MPU_ATTR_MEMORY_(0UL, 1UL, 1UL, 1UL), /* Outer Write-Back transient with read and write allocate */
		ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)  /* Inner Write-Through transient with read and write allocate */
	));

	ARM_MPU_SetRegion(0UL,
		ARM_MPU_RBAR(0x08000000UL, ARM_MPU_SH_NON, 0UL, 1UL, 1UL),  /* Non-shareable, read/write, non-privileged, execute-never */
		ARM_MPU_RLAR(0x080FFFFFUL, 0UL)                             /* 1MB memory block using Attr 0 */
	);

	ARM_MPU_Enable(0);

	// Execute application code that is access protected by the MPU

	ARM_MPU_Disable();

	return 0;
}

const ARM_MPU_Region_t mpuTable[1][4] = {
  {
    //                     BASE          SH              RO   NP   XN                         LIMIT         ATTR 
    { .RBAR = ARM_MPU_RBAR(0x08000000UL, ARM_MPU_SH_NON, 0UL, 1UL, 0UL), .RLAR = ARM_MPU_RLAR(0x080FFFFFUL, 0UL) },
    { .RBAR = ARM_MPU_RBAR(0x20000000UL, ARM_MPU_SH_NON, 0UL, 1UL, 1UL), .RLAR = ARM_MPU_RLAR(0x20007FFFUL, 0UL) },
    { .RBAR = ARM_MPU_RBAR(0x40020000UL, ARM_MPU_SH_NON, 0UL, 1UL, 1UL), .RLAR = ARM_MPU_RLAR(0x40021FFFUL, 1UL) },
    { .RBAR = ARM_MPU_RBAR(0x40022000UL, ARM_MPU_SH_NON, 0UL, 1UL, 1UL), .RLAR = ARM_MPU_RLAR(0x40022FFFUL, 1UL) }
  }
};
 
void UpdateMpu(uint32_t idx)
{
   ARM_MPU_Load(0, mpuTable[idx], 4);
}
#endif

#define CONFIG_MPU_WZL                   1

#if CONFIG_MPU_WZL
void mpu_setup(void)
{
	uint32_t region_num;
	
	ARM_MPU_Disable();
	region_num = mpu_get_type();

	/*default 8 regions*/
	/*No 0*/
	#if MPU_INIT_REGION0
	bk_secure_printf("[MPU Region]MPU_INIT_REGION0\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_0, REGION0_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_0, REGION0_RBAR, REGION0_RBLAR);
	#endif
	
	/*No 1*/
	#if MPU_INIT_REGION1
	bk_secure_printf("[MPU Region]MPU_INIT_REGION1\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_1, REGION1_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_1, REGION1_RBAR, REGION1_RBLAR);
	#endif
	
	/*No 2*/
	#if MPU_INIT_REGION2
	bk_secure_printf("[MPU Region]MPU_INIT_REGION2\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_2, REGION2_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_2, REGION2_RBAR, REGION2_RBLAR);
	#endif
	
	/*No 3*/
	#if MPU_INIT_REGION3
	bk_secure_printf("[MPU Region]MPU_INIT_REGION3\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_3, REGION3_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_3, REGION3_RBAR, REGION3_RBLAR);
	#endif
	
	/*No 4*/
	#if MPU_INIT_REGION4
	bk_secure_printf("[MPU Region]MPU_INIT_REGION4\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_4, REGION4_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_4, REGION4_RBAR, REGION4_RBLAR);
	#endif
	
	/*No 5*/
	#if MPU_INIT_REGION5
	bk_secure_printf("[MPU Region]MPU_INIT_REGION5\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_5, REGION5_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_5, REGION5_RBAR, REGION5_RBLAR);
	#endif
	
	/*No 6*/
	#if MPU_INIT_REGION6
	bk_secure_printf("[MPU Region]MPU_INIT_REGION6\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_6, REGION6_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_6, REGION6_RBAR, REGION6_RBLAR);
	#endif
	
	/*No 7*/
	#if MPU_INIT_REGION7
	bk_secure_printf("[MPU Region]MPU_INIT_REGION7\r\n");
	ARM_MPU_SetMemAttr(MPU_REGION_7, REGION7_ATTR);
	ARM_MPU_SetRegion(MPU_REGION_7, REGION7_RBAR, REGION7_RBLAR);
	#endif
	
	bk_secure_printf("[MPU]ARM_MPU_Enable\r\n");	
	ARM_MPU_Enable(1);
}
#else

#define WCL_MPU_TYPE (*(volatile unsigned long*)(0xE000ED90UL))  
#define WCL_MPU_CTRL (*(volatile unsigned long*)(0xE000ED94UL)) 
#define WCL_MPU_RNR (*(volatile unsigned long*)(0xE000ED98UL))
#define WCL_MPU_RBAR (*(volatile unsigned long*)(0xE000ED9CUL))
#define WCL_MPU_RLAR (*(volatile unsigned long*)(0xE000EDA0UL))
#define WCL_MPU_RBAR_A (*(volatile unsigned long*)(0xE000EDA4UL))
#define WCL_MPU_RLAR_A (*(volatile unsigned long*)(0xE000EDA8UL))
#define WCL_MPU_MAIR0 (*(volatile unsigned long*)(0xE000EDC0UL))
#define WCL_MPU_MAIR1 (*(volatile unsigned long*)(0xE000EDC4UL))

void mpu_setup(void)
{
	WCL_MPU_MAIR0 = 0x00000033;
	WCL_MPU_MAIR1 = 0x0000000C;
	
	WCL_MPU_RNR = 0;
	WCL_MPU_RBAR = (0x20000000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x20008000 & 0xFFFFFFC0) | (0x00 << 1) | 0x01;
	
	WCL_MPU_RNR = 1;
	WCL_MPU_RBAR = (0x20008000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x20010000 & 0xFFFFFFC0) | (0x00 << 1) | 0x01;
	
	WCL_MPU_RNR = 2;
	WCL_MPU_RBAR = (0x20010000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x20020000 & 0xFFFFFFC0) | (0x00 << 1) | 0x01;
	
	WCL_MPU_RNR = 3;
	WCL_MPU_RBAR = (0x20020000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x20028000 & 0xFFFFFFC0) | (0x00 << 1) | 0x01;
	
	WCL_MPU_RNR = 4;
	WCL_MPU_RBAR = (0x20028000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x20800000 & 0xFFFFFFC0) | (0x00 << 1) | 0x01;
	
	WCL_MPU_RNR = 5;
	WCL_MPU_RBAR = (0x70000000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x70800000 & 0xFFFFFFC0) | (0x04 << 1) | 0x01;
	
	WCL_MPU_RNR = 6;
	WCL_MPU_RBAR = (0x00000000 & 0xFFFFFFC0) | (0x00 << 3) | (0x03 << 1) | 0x00;
	WCL_MPU_RLAR = (0x00800000 & 0xFFFFFFC0) | (0x00 << 1) | 0x01;

	WCL_MPU_RNR = 7;
	WCL_MPU_RBAR = (0x40000000 & 0xFFFFFFC0) | (0x00 << 3) | (0x01 << 1) | 0x01;
	WCL_MPU_RLAR = (0x40800000 & 0xFFFFFFC0) | (0x04 << 1) | 0x01;
	
	WCL_MPU_CTRL = (0x00 << 2) | 0x01;
}
#endif

// eof
