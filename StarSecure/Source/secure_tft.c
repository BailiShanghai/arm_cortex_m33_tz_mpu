#include <stdio.h>
#include <stdint.h>

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

struct boot_arm_vector_table
{
    uint32_t msp;
    uint32_t reset;
};

#define LOADER_NS_CODE_START 0x0000F000


static struct boot_arm_vector_table *vt = (struct boot_arm_vector_table *)LOADER_NS_CODE_START;

#if 0
__attribute__((naked)) void boot_stm_jump_to_next_image(uint32_t boot_jump_addr, uint32_t reset_handler_addr)
{
    __ASM volatile(
#if !defined(__ICCARM__)
        ".syntax unified                 \n"
#endif
        "mov     r7, r0                  \n"
        "mov     r8, r1                  \n"
        "bl      boot_clear_bl2_ram_area \n" /* Clear RAM before jump */
        "movs    r0, #0                  \n" /* Clear registers: R0-R12, */
        "mov     r1, r0                  \n" /* except R7 */
        "mov     r2, r0                  \n"
        "mov     r3, r0                  \n"
        "mov     r4, r0                  \n"
        "mov     r5, r0                  \n"
        "mov     r6, r0                  \n"
        "mov     r9, r0                  \n"
        "mov     r10, r0                 \n"
        "mov     r11, r0                 \n"
        "mov     r12, r0                 \n"
        "mov     lr,  r0                 \n"
        "mov     r0, r8                  \n"
        "mov     r8, r1                  \n"
        "bx      r7                      \n" /* Jump to Reset_handler */
    );
}

__attribute__((naked)) void boot_jump_to_ns_image(uint32_t reset_handler_addr)
{
    __ASM volatile(
#if !defined(__ICCARM__)
        ".syntax unified                 \n"
#endif /* !defined(__ICCARM__) */
        "mov     r7, r0                  \n"
        "bl      boot_clean_ns_ram_area  \n" /* Clean all RAM and unsecure all before jump */
        "movs    r0, #0                  \n" /* Clear registers: R0-R12, */
        "mov     r1, r0                  \n" /* except R7 */
        "mov     r2, r0                  \n"
        "mov     r3, r0                  \n"
        "mov     r4, r0                  \n"
        "mov     r5, r0                  \n"
        "mov     r6, r0                  \n"
        "mov     r8, r0                  \n"
        "mov     r9, r0                  \n"
        "mov     r10, r0                 \n"
        "mov     r11, r0                 \n"
        "mov     r12, r0                 \n"
        "mov     lr,  r0                 \n"
        "bic.w   r7, r7, #1              \n"
        "blxns   r7                      \n" /* Jump to non secure Reset_handler */
    );
}

#else
__attribute__((naked)) void boot_stm_jump_to_next_image(uint32_t boot_jump_addr, uint32_t reset_handler_addr)
{
    __ASM volatile(
#if !defined(__ICCARM__)
        ".syntax unified                 \n"
#endif
        "mov     r7, r0                  \n"
        "mov     r8, r1                  \n"
        "movs    r0, #0                  \n" /* Clear registers: R0-R12, */
        "mov     r1, r0                  \n" /* except R7 */
        "mov     r2, r0                  \n"
        "mov     r3, r0                  \n"
        "mov     r4, r0                  \n"
        "mov     r5, r0                  \n"
        "mov     r6, r0                  \n"
        "mov     r9, r0                  \n"
        "mov     r10, r0                 \n"
        "mov     r11, r0                 \n"
        "mov     r12, r0                 \n"
        "mov     lr,  r0                 \n"
        "mov     r0, r8                  \n"
        "mov     r8, r1                  \n"
        "bx      r7                      \n" /* Jump to Reset_handler */
    );
}

__attribute__((naked)) void boot_jump_to_ns_image(uint32_t reset_handler_addr)
{
    __ASM volatile(
#if !defined(__ICCARM__)
        ".syntax unified                 \n"
#endif /* !defined(__ICCARM__) */
        "mov     r7, r0                  \n"
        "movs    r0, #0                  \n" /* Clear registers: R0-R12, */
        "mov     r1, r0                  \n" /* except R7 */
        "mov     r2, r0                  \n"
        "mov     r3, r0                  \n"
        "mov     r4, r0                  \n"
        "mov     r5, r0                  \n"
        "mov     r6, r0                  \n"
        "mov     r8, r0                  \n"
        "mov     r9, r0                  \n"
        "mov     r10, r0                 \n"
        "mov     r11, r0                 \n"
        "mov     r12, r0                 \n"
        "mov     lr,  r0                 \n"
        "bic.w   r7, r7, #1              \n"
        "blxns   r7                      \n" /* Jump to non secure Reset_handler */
    );
}

#endif

/**
 * Jump to unsafe mode
 */
void jump_to_no_secure(void)
{
    static struct boot_arm_vector_table *vt = (struct boot_arm_vector_table *)LOADER_NS_CODE_START;

    SCB_NS->VTOR = LOADER_NS_CODE_START;

    __TZ_set_MSP_NS((*(uint32_t *)LOADER_NS_CODE_START));

    boot_stm_jump_to_next_image((uint32_t)&boot_jump_to_ns_image, vt->reset);
}