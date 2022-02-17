
int bk_secure_printf(const char *fmt, ...);

//#pragma clang section text="SEC_XO"
void xo_f_test(void) __attribute__((section("SEC_XO")));
void xo_f_test(void)
{
	bk_secure_printf("xo_f_test\r\n");
}
// eof


