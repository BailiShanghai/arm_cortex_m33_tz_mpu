#include "sfv_s.h"
#include "platform_generic.h"

/* 
 * Secure/Non-Secure
 * Privileged/Non-privileged
 * Read-only
 * Read/Write
 * Execute only
 * Execute-Never.
 * No Access
 */
 
void sfv_switch_to_unprivilege_level(void)
{
	bk_secure_printf("[SFV]control register:0x%x\r\n", __get_CONTROL());
	__set_CONTROL(0x01);
	bk_secure_printf("[SFV]set control register:0x%x\r\n", __get_CONTROL());
}

void sfv_switch_to_privilege_level(void)
{
	/* exception or interrupts
     * __svc(5);
     */ 
	__asm volatile ( "svc %0 \n" ::"i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );
}

void sfv_ro_section_verify(void *ro_sec_ptr, uint32_t ro_sec_len)
{
	uint32_t *addr = (uint32_t *)ro_sec_ptr;
	
	bk_secure_printf("[RO]read addr:0x%x val:0x%x\r\n", addr, *addr);
	
	bk_secure_printf("[RO]write addr:0x%x val:0x%x\r\n", addr, 0x5a5a);
	*addr = 0x5a5a;
}

void sfv_rw_section_verify(void *rw_sec_ptr, uint32_t rw_sec_len)
{
	uint32_t *addr = (uint32_t *)rw_sec_ptr;
	
	bk_secure_printf("[RW]read addr:0x%x val:0x%x\r\n", addr, *addr);
	
	bk_secure_printf("[RW]write addr:0x%x val:0x%x\r\n", addr, 0x5a5a);
	*addr = 0x5a5a;
}

void sfv_xo_section_verify(void *xo_sec_ptr, uint32_t xo_sec_len)
{
	FUNC_PTR func = (FUNC_PTR *)xo_sec_ptr;
	uint32_t *addr = (uint32_t *)xo_sec_ptr;
	
	bk_secure_printf("[XO]read addr:0x%x val:0x%x\r\n", addr, *addr);
	
	bk_secure_printf("[XO]write addr:0x%x val:0x%x\r\n", addr, 0x5a5a);
	*addr = 0x5a5a;

	(*func)();
}

void sfv_xn_section_verify(void *xn_sec_ptr, uint32_t xn_sec_len)
{
	FUNC_PTR func = (FUNC_PTR *)xn_sec_ptr;
	uint32_t *addr = (uint32_t *)xn_sec_ptr;
	
	bk_secure_printf("[XN]read addr:0x%x val:0x%x\r\n", addr, *addr);
	
	bk_secure_printf("[XN]write addr:0x%x val:0x%x\r\n", addr, 0x5a5a);
	*addr = 0x5a5a;

	(*func)();
}

void sfv_na_section_verify(void *na_sec_ptr, uint32_t na_sec_len)
{
	uint32_t *addr = (uint32_t *)na_sec_ptr;
	
	bk_secure_printf("[NA]read addr:0x%x val:0x%x\r\n", addr, *addr);
	
	bk_secure_printf("[NA]write addr:0x%x val:0x%x\r\n", addr, 0x5a5a);
	*addr = 0x5a5a;
}

void sfv_section_verify(void)
{
	sfv_ro_section_verify(SECTION_RO_ADDR, SECTION_RO_LEN);
	sfv_rw_section_verify(SECTION_RW_ADDR, SECTION_RW_LEN);
	sfv_xo_section_verify(SECTION_XO_ADDR, SECTION_XO_LEN);
	sfv_xn_section_verify(SECTION_XN_ADDR, SECTION_XN_LEN);
	sfv_na_section_verify(SECTION_NA_ADDR, SECTION_NA_LEN);
}

void sfv_verify_privilege(void)
{
	sfv_section_verify();
}

void sfv_verify_unprivilege(void)
{
	sfv_section_verify();
}

void sfv_verify(void)
{
	sfv_verify_privilege();
	sfv_switch_to_unprivilege_level();
	sfv_verify_unprivilege();	
}
// eof

