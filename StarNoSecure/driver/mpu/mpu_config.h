#ifndef _MPU_CONFIG_H_
#define _MPU_CONFIG_H_

#include "mpu_armstar_m33.h"

enum
{
    MPU_REGION_0 = 0,
    MPU_REGION_1,
    MPU_REGION_2,
    MPU_REGION_3,
    MPU_REGION_4,
    MPU_REGION_5,
    MPU_REGION_6,
    MPU_REGION_7,
};

#define CONFIG_MPU_WITH_S_ADDRESS_ORDER               1

#if CONFIG_MPU_FROM_WCLIN
#define MPU_INIT_REGION0    1
#define MPU_INIT_REGION1    1
#define MPU_INIT_REGION2    1
#define MPU_INIT_REGION3    0
#define MPU_INIT_REGION4    0
#define MPU_INIT_REGION5    0
#define MPU_INIT_REGION6    0
#define MPU_INIT_REGION7    0


#define REGION0_RBAR                  (0x0 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RO_APL << MPU_RBAR_AP_Pos) + (MPU_AP_X_SET << MPU_RBAR_XN_Pos))
#define REGION0_RBLAR                 (0x00800000 + (0 << 1) + MPU_RLAR_REGION_ENABLE)
/** \brief Attribute for normal memory (outer and inner)
*  ARM_MPU_ATTR_MEMORY_(NT, WB, RA, WA)
* \param NT Non-Transient: Set to 1 for non-transient data.
* \param WB Write-Back: Set to 1 to use write-back update policy.
* \param RA Read Allocation: Set to 1 to use cache allocation on read miss.
* \param WA Write Allocation: Set to 1 to use cache allocation on write miss.
*/
#define REGION0_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION1_RBAR                  (0x20000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION1_RBLAR                 (0x20800000 + (1 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION1_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION2_RBAR                  (0x40000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION2_RBLAR                 (0x40800000 + (2 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION2_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 0UL, 0UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION3_RBAR                  (0x70000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION3_RBLAR                 (0x70800000 + (3 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION3_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 0UL, 0UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#undef MPU_INIT_REGION4
#undef MPU_INIT_REGION5
#undef MPU_INIT_REGION6
#undef MPU_INIT_REGION7
#endif

#if CONFIG_MPU_WITH_S_ADDRESS
#define MPU_INIT_REGION0    1
#define MPU_INIT_REGION1    1
#define MPU_INIT_REGION2    1
#define MPU_INIT_REGION3    1
#define MPU_INIT_REGION4    1
#define MPU_INIT_REGION5    1
#define MPU_INIT_REGION6    1
#define MPU_INIT_REGION7    1

#define NS_DATA_OFFSET                (0)  // 0x00100000

#define REGION0_RBAR                  (NS_DATA_OFFSET + 0x20000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION0_RBLAR                 (NS_DATA_OFFSET + 0x20008000 + (0 << 1) + MPU_RLAR_REGION_ENABLE) // 0x20008000
/** \brief Attribute for normal memory (outer and inner)
*  ARM_MPU_ATTR_MEMORY_(NT, WB, RA, WA)
* \param NT Non-Transient: Set to 1 for non-transient data.
* \param WB Write-Back: Set to 1 to use write-back update policy.
* \param RA Read Allocation: Set to 1 to use cache allocation on read miss.
* \param WA Write Allocation: Set to 1 to use cache allocation on write miss.
*/
#define REGION0_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION1_RBAR                  (NS_DATA_OFFSET + 0x20008000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION1_RBLAR                 (NS_DATA_OFFSET + 0x20010000 + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION1_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION2_RBAR                  (NS_DATA_OFFSET + 0x20010000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION2_RBLAR                 (NS_DATA_OFFSET + 0x20020000 + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION2_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION3_RBAR                  (NS_DATA_OFFSET + 0x20020000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION3_RBLAR                 (NS_DATA_OFFSET + 0x20028000 + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION3_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION4_RBAR                  (NS_DATA_OFFSET + 0x20028000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION4_RBLAR                 (NS_DATA_OFFSET + 0x20800000 + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION4_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION5_RBAR                  (0x70000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION5_RBLAR                 (0x70800000 + (5 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION5_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 0UL, 0UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION6_RBAR                  (NS_DATA_OFFSET + 0 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RO_APL << MPU_RBAR_AP_Pos) + (MPU_AP_X_SET << MPU_RBAR_XN_Pos))
#define REGION6_RBLAR                 (NS_DATA_OFFSET + 0x00800000 + (6 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION6_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION7_RBAR                  (NS_DATA_OFFSET + 0x40000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION7_RBLAR                 (NS_DATA_OFFSET + 0x40800000 + (7 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION7_ATTR                  (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 0UL, 0UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#endif

#if CONFIG_MPU_WITH_S_ADDRESS_ORDER
#define MPU_INIT_REGION0    1
#define MPU_INIT_REGION1    1
#define MPU_INIT_REGION2    1
#define MPU_INIT_REGION3    1
#define MPU_INIT_REGION4    1
#define MPU_INIT_REGION5    1
#define MPU_INIT_REGION6    1
#define MPU_INIT_REGION7    1

#define REGION0_RBAR         (0x20000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION0_RBLAR        ((0x20020000 - 32) + (0 << 1) + MPU_RLAR_REGION_ENABLE)
/** \brief Attribute for normal memory (outer and inner)
*  ARM_MPU_ATTR_MEMORY_(NT, WB, RA, WA)
* \param NT Non-Transient: Set to 1 for non-transient data.
* \param WB Write-Back: Set to 1 to use write-back update policy.
* \param RA Read Allocation: Set to 1 to use cache allocation on read miss.
* \param WA Write Allocation: Set to 1 to use cache allocation on write miss.
*/
#define REGION0_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION1_RBAR        (0x20020000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION1_RBLAR       ((0x20020800 - 0) + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION1_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION2_RBAR        ((0x20020800 + 32) + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RO_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION2_RBLAR       ((0x20021000 - 32) + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION2_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION3_RBAR        (0x20021000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_X_SET << MPU_RBAR_XN_Pos))
#define REGION3_RBLAR       ((0x20021800 - 32) + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION3_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION4_RBAR        (0x20021800 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION4_RBLAR       ((0x20800000 - 0) + (0 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION4_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION5_RBAR        (0x70000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION5_RBLAR       ((0x70800000 - 0) + (5 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION5_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 0UL, 0UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION6_RBAR        (0 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RO_APL << MPU_RBAR_AP_Pos) + (MPU_AP_X_SET << MPU_RBAR_XN_Pos))
#define REGION6_RBLAR       ((0x00800000 - 0) + (6 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION6_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))

#define REGION7_RBAR        (0x40000000 + (ARM_MPU_SH_NON << MPU_RBAR_SH_Pos) + (MPU_AP_RW_APL << MPU_RBAR_AP_Pos) + (MPU_AP_XN << MPU_RBAR_XN_Pos))
#define REGION7_RBLAR       ((0x40800000 - 0) + (7 << 1) + MPU_RLAR_REGION_ENABLE)
#define REGION7_ATTR        (ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 0UL, 0UL), ARM_MPU_ATTR_MEMORY_(0UL, 0UL, 1UL, 1UL)))
#endif
#endif //_MPU_CONFIG_H_
//eof

