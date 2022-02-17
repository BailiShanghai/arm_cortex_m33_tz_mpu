
int bk_secure_printf(const char *fmt, ...);

//#pragma clang section text="SEC_XN"
void xn_f_test(void) __attribute__((section ("SEC_XN")));
void xn_f_test(void)
{
	bk_secure_printf("xn_f_test\r\n");
}
// eof


