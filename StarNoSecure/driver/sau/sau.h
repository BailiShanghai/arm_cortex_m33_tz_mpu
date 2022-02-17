#ifndef _SAU_H_
#define _SAU_H_

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SAU     Security Attribution Unit (SAU)
  \brief    Type definitions for the Security Attribution Unit (SAU)
  @{
 */

/**
  \brief  Structure type to access the Security Attribution Unit (SAU).
 */
typedef struct
{
    __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SAU Control Register */
    __IM  uint32_t TYPE;                   /*!< Offset: 0x004 (R/ )  SAU Type Register */
#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
    __IOM uint32_t RNR;                    /*!< Offset: 0x008 (R/W)  SAU Region Number Register */
    __IOM uint32_t RBAR;                   /*!< Offset: 0x00C (R/W)  SAU Region Base Address Register */
    __IOM uint32_t RLAR;                   /*!< Offset: 0x010 (R/W)  SAU Region Limit Address Register */
#else
    uint32_t RESERVED0[3];
#endif
    __IOM uint32_t SFSR;                   /*!< Offset: 0x014 (R/W)  Secure Fault Status Register */
    __IOM uint32_t SFAR;                   /*!< Offset: 0x018 (R/W)  Secure Fault Address Register */
} SAU_Type;

/* SAU Control Register Definitions */
#define SAU_CTRL_ALLNS_Pos                  1U                                            /*!< SAU CTRL: ALLNS Position */
#define SAU_CTRL_ALLNS_Msk                 (1UL << SAU_CTRL_ALLNS_Pos)                    /*!< SAU CTRL: ALLNS Mask */

#define SAU_CTRL_ENABLE_Pos                 0U                                            /*!< SAU CTRL: ENABLE Position */
#define SAU_CTRL_ENABLE_Msk                (1UL /*<< SAU_CTRL_ENABLE_Pos*/)               /*!< SAU CTRL: ENABLE Mask */

/* SAU Type Register Definitions */
#define SAU_TYPE_SREGION_Pos                0U                                            /*!< SAU TYPE: SREGION Position */
#define SAU_TYPE_SREGION_Msk               (0xFFUL /*<< SAU_TYPE_SREGION_Pos*/)           /*!< SAU TYPE: SREGION Mask */

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
/* SAU Region Number Register Definitions */
#define SAU_RNR_REGION_Pos                  0U                                            /*!< SAU RNR: REGION Position */
#define SAU_RNR_REGION_Msk                 (0xFFUL /*<< SAU_RNR_REGION_Pos*/)             /*!< SAU RNR: REGION Mask */

/* SAU Region Base Address Register Definitions */
#define SAU_RBAR_BADDR_Pos                  5U                                            /*!< SAU RBAR: BADDR Position */
#define SAU_RBAR_BADDR_Msk                 (0x7FFFFFFUL << SAU_RBAR_BADDR_Pos)            /*!< SAU RBAR: BADDR Mask */

/* SAU Region Limit Address Register Definitions */
#define SAU_RLAR_LADDR_Pos                  5U                                            /*!< SAU RLAR: LADDR Position */
#define SAU_RLAR_LADDR_Msk                 (0x7FFFFFFUL << SAU_RLAR_LADDR_Pos)            /*!< SAU RLAR: LADDR Mask */

#define SAU_RLAR_NSC_Pos                    1U                                            /*!< SAU RLAR: NSC Position */
#define SAU_RLAR_NSC_Msk                   (1UL << SAU_RLAR_NSC_Pos)                      /*!< SAU RLAR: NSC Mask */

#define SAU_RLAR_ENABLE_Pos                 0U                                            /*!< SAU RLAR: ENABLE Position */
#define SAU_RLAR_ENABLE_Msk                (1UL /*<< SAU_RLAR_ENABLE_Pos*/)               /*!< SAU RLAR: ENABLE Mask */

#endif /* defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U) */

/* Secure Fault Status Register Definitions */
#define SAU_SFSR_LSERR_Pos                  7U                                            /*!< SAU SFSR: LSERR Position */
#define SAU_SFSR_LSERR_Msk                 (1UL << SAU_SFSR_LSERR_Pos)                    /*!< SAU SFSR: LSERR Mask */

#define SAU_SFSR_SFARVALID_Pos              6U                                            /*!< SAU SFSR: SFARVALID Position */
#define SAU_SFSR_SFARVALID_Msk             (1UL << SAU_SFSR_SFARVALID_Pos)                /*!< SAU SFSR: SFARVALID Mask */

#define SAU_SFSR_LSPERR_Pos                 5U                                            /*!< SAU SFSR: LSPERR Position */
#define SAU_SFSR_LSPERR_Msk                (1UL << SAU_SFSR_LSPERR_Pos)                   /*!< SAU SFSR: LSPERR Mask */

#define SAU_SFSR_INVTRAN_Pos                4U                                            /*!< SAU SFSR: INVTRAN Position */
#define SAU_SFSR_INVTRAN_Msk               (1UL << SAU_SFSR_INVTRAN_Pos)                  /*!< SAU SFSR: INVTRAN Mask */

#define SAU_SFSR_AUVIOL_Pos                 3U                                            /*!< SAU SFSR: AUVIOL Position */
#define SAU_SFSR_AUVIOL_Msk                (1UL << SAU_SFSR_AUVIOL_Pos)                   /*!< SAU SFSR: AUVIOL Mask */

#define SAU_SFSR_INVER_Pos                  2U                                            /*!< SAU SFSR: INVER Position */
#define SAU_SFSR_INVER_Msk                 (1UL << SAU_SFSR_INVER_Pos)                    /*!< SAU SFSR: INVER Mask */

#define SAU_SFSR_INVIS_Pos                  1U                                            /*!< SAU SFSR: INVIS Position */
#define SAU_SFSR_INVIS_Msk                 (1UL << SAU_SFSR_INVIS_Pos)                    /*!< SAU SFSR: INVIS Mask */

#define SAU_SFSR_INVEP_Pos                  0U                                            /*!< SAU SFSR: INVEP Position */
#define SAU_SFSR_INVEP_Msk                 (1UL /*<< SAU_SFSR_INVEP_Pos*/)                /*!< SAU SFSR: INVEP Mask */

/*@} end of group CMSIS_SAU */
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */


#endif
// eof
