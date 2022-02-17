
int bk_secure_printf(const char *fmt, ...);

//#pragma clang section text="SEC_RO"
void ro_f_test(void) __attribute__((section("SEC_RO")));
void ro_f_test(void)
{
	bk_secure_printf("ro_f_test\r\n");
}
// eof

