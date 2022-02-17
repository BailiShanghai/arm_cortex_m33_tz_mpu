#ifndef _SFV_S_H_
#define _SFV_S_H_

/* 
 * Secure/Non-Secure
 * Privileged/Non-privileged
 * Read-only
 * Read/Write
 * Execute only
 * Execute-Never.
 * No Access
 */
#define SECTION_RO_ADDR             (0x20020820) 
#define SECTION_RO_LEN              (0x800) 

#define SECTION_RW_ADDR             (0x20020420) 
#define SECTION_RW_LEN              (32) 

#define SECTION_XO_ADDR             (0x20021000) 
#define SECTION_XO_LEN              (0x100) 

#define SECTION_XN_ADDR             (0x20021800) 
#define SECTION_XN_LEN              (0x800) 

#define SECTION_NA_ADDR             (0x20020800) 
#define SECTION_NA_LEN              (32) 

#define portSVC_RAISE_PRIVILEGE 		   3

#endif // _SFV_S_H_
// eof
