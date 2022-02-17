#ifndef _MPU_H_
#define _MPU_H_

#define __MPU_PRESENT__          0

#define MPU_INIT_REGION0    1
#define MPU_INIT_REGION1    0
#define MPU_INIT_REGION2    0
#define MPU_INIT_REGION3    0
#define MPU_INIT_REGION4    0
#define MPU_INIT_REGION5    0
#define MPU_INIT_REGION6    0
#define MPU_INIT_REGION7    0

/*
Address       Name     Type        Reset Value                  Description
E000ED90      MPU_TYPE RO          The reset value is fixed     See 4.5.10 MPU Type Register on page 4-351.
                                   and depends on the value
                                   of bits[15:8] and
                                   implementation options.

0xE000ED94   MPU_CTRL  RW          0x00000000                   See 4.5.11 MPU Control Register on page 4-352.
0xE000ED98   MPU_RNR   RW          UNKNOWN                      See 4.5.12 MPU Region Number Register on page 4-353.
0xE000ED9C   MPU_RBAR  RW          UNKNOWN                      See 4.5.13 MPU Region Base Address Register on page 4-354.
0xE000EDA0   MPU_RLAR  RW          UNKNOWN                      See 4.5.15 MPU Region Limit Address Register on page 4-355.
E000EDA4     MPU_RBAR_A<n> RW      UNKNOWN                      See 4.5.14 MPU Region Base Address Register Alias,n=1-3 on page 4-355.
E000EDA8     MPU_RLAR_A<n> RW      UNKNOWN                      See 4.5.16 MPU Region Limit Address Register Alias,n=1-3 on page 4-356.
0xE000EDC0   MPU_MAIR0 RW          UNKNOWN                      See 4.5.17 MPU Memory Attribute Indirection Registers 0 and 1 on page 4-356.
0xE000EDC4   MPU_MAIR1 RW          UNKNOWN                      See 4.5.17 MPU Memory Attribute Indirection Registers 0 and 1 on page 4-356.
*/
#define MPU_SECURE_WORLD          (0)
#define MPU_SE_BASE               (0x20000)
#define MPU_BASE_ADDR             (0xE000ED90 + MPU_SE_BASE * MPU_SECURE_WORLD)

#define MPU_TYPE                  (MPU_BASE_ADDR + 0 * 4)
#define MPU_CTRL                  (MPU_BASE_ADDR + 1 * 4)
#define MPU_RNR                   (MPU_BASE_ADDR + 2 * 4)
#define MPU_RBAR                  (MPU_BASE_ADDR + 3 * 4)
#define MPU_RLAR                  (MPU_BASE_ADDR + 4 * 4)
#define MPU_RBAR_A1               (MPU_BASE_ADDR + 5 * 4)
#define MPU_RBAR_A2               (MPU_BASE_ADDR + 5 * 4)
#define MPU_RBAR_A3               (MPU_BASE_ADDR + 5 * 4)
#define MPU_RLAR_A1               (MPU_BASE_ADDR + 6 * 4)
#define MPU_RLAR_A2               (MPU_BASE_ADDR + 6 * 4)
#define MPU_RLAR_A3               (MPU_BASE_ADDR + 6 * 4)
#define MPU_MAIR0                 (MPU_BASE_ADDR + 12 * 4)
#define MPU_MAIR1                 (MPU_BASE_ADDR + 13 * 4)

#if defined (__MPU_PRESENT__) && (__MPU_PRESENT__ == 1U)
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_MPU     Memory Protection Unit (MPU)
  \brief    Type definitions for the Memory Protection Unit (MPU)
  @{
 */

struct mpu_region_t
{
    uint32_t start_addr;
    uint32_t limit_addr;
    uint8_t id;
    uint8_t attr;
    uint8_t padding[2];
};

/**
  \brief  Structure type to access the Memory Protection Unit (MPU).
 */
typedef struct
{
    _RO_ uint32_t TYPE;
    _RW_ uint32_t CTRL;

    _RW_ uint32_t RNR;

    _RW_ uint32_t RBAR;
    _RW_ uint32_t RLAR;

    uint32_t RESERVED0[7];
    union
    {
        _RW_ uint32_t MAIR[2];
        struct
        {
            _RW_ uint32_t MAIR0;
            _RW_ uint32_t MAIR1;
        };
    };
} MPU_HW;

#define MPU_TYPE_RALIASES                  4U

/* MPU Type Register Definitions */
#define MPU_TYPE_DREGION_POS                8U
#define MPU_TYPE_DREGION_MSK               (0xFFUL << MPU_TYPE_DREGION_POS)

#define MPU_TYPE_SEPARATE_POS               0U
#define MPU_TYPE_SEPARATE_MSK              (1UL /*<< MPU_TYPE_SEPARATE_POS*/)

/* MPU Control Register Definitions */
#define MPU_CTRL_PRIVDEFENA_POS             2U
#define MPU_CTRL_PRIVDEFENA_MSK            (1UL << MPU_CTRL_PRIVDEFENA_POS)

#define MPU_CTRL_HFNMIENA_POS               1U
#define MPU_CTRL_HFNMIENA_MSK              (1UL << MPU_CTRL_HFNMIENA_POS)

#define MPU_CTRL_ENABLE_POS                 0U
#define MPU_CTRL_ENABLE_MSK                (1UL /*<< MPU_CTRL_ENABLE_POS*/)

/* MPU Region Number Register Definitions */
#define MPU_RNR_REGION_POS                  0U
#define MPU_RNR_REGION_MSK                 (0xFFUL /*<< MPU_RNR_REGION_POS*/)

/* MPU Region Base Address Register Definitions */
#define MPU_RBAR_BASE_POS                   5U
#define MPU_RBAR_BASE_MSK                  (0x7FFFFFFUL << MPU_RBAR_BASE_POS)

#define MPU_RBAR_SH_POS                     3U
#define MPU_RBAR_SH_MSK                    (0x3UL << MPU_RBAR_SH_POS)

#define MPU_RBAR_AP_POS                     1U
#define MPU_RBAR_AP_MSK                    (0x3UL << MPU_RBAR_AP_POS)

#define MPU_RBAR_XN_POS                     0U
#define MPU_RBAR_XN_MSK                    (01UL /*<< MPU_RBAR_XN_POS*/)

/* MPU Region Limit Address Register Definitions */
#define MPU_RLAR_LIMIT_POS                  5U
#define MPU_RLAR_LIMIT_MSK                 (0x7FFFFFFUL << MPU_RLAR_LIMIT_POS)

#define MPU_RLAR_ATTR_ID__POS               1U
#define MPU_RLAR_ATTR_ID__MSK              (0x7UL << MPU_RLAR_ATTR_ID__POS)

#define MPU_RLAR_EN_POS                     0U
#define MPU_RLAR_EN_MSK                    (1UL /*<< MPU_RLAR_EN_POS*/)

/* MPU Memory Attribute Indirection Register 0 Definitions */
#define MPU_MAIR0_ATTR3_POS                24U
#define MPU_MAIR0_ATTR3_MSK                (0xFFUL << MPU_MAIR0_ATTR3_POS)

#define MPU_MAIR0_ATTR2_POS                16U
#define MPU_MAIR0_ATTR2_MSK                (0xFFUL << MPU_MAIR0_ATTR2_POS)

#define MPU_MAIR0_ATTR1_POS                 8U
#define MPU_MAIR0_ATTR1_MSK                (0xFFUL << MPU_MAIR0_ATTR1_POS)

#define MPU_MAIR0_ATTR0_POS                 0U
#define MPU_MAIR0_ATTR0_MSK                (0xFFUL /*<< MPU_MAIR0_ATTR0_POS*/)

/* MPU Memory Attribute Indirection Register 1 Definitions */
#define MPU_MAIR1_ATTR7_POS                24U
#define MPU_MAIR1_ATTR7_MSK                (0xFFUL << MPU_MAIR1_ATTR7_POS)

#define MPU_MAIR1_ATTR6_POS                16U
#define MPU_MAIR1_ATTR6_MSK                (0xFFUL << MPU_MAIR1_ATTR6_POS)

#define MPU_MAIR1_ATTR5_POS                 8U
#define MPU_MAIR1_ATTR5_MSK                (0xFFUL << MPU_MAIR1_ATTR5_POS)

#define MPU_MAIR1_ATTR4_POS                 0U
#define MPU_MAIR1_ATTR4_MSK                (0xFFUL /*<< MPU_MAIR1_ATTR4_POS*/)

/*@} end of group CMSIS_MPU */
#endif

void mpu_setup(void);

#endif // _MPU_H_
// eof
