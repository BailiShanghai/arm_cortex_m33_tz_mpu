#ifndef _PLATFORM_GENERIC_H_
#define _PLATFORM_GENERIC_H_

#include "cm_backtrace.h"
#include "sys_config.h"

typedef void (*FUNC_PTR)(void);

static inline void _platform_assert(void)
{
	#if (CONFIG_ENABLE_CM_BACKTRACE) 
	    cm_backtrace_assert(__current_sp());
    #else 
		while(1);
    #endif 
}

#define PF_ASSERT(exp) \
	do\
	{\
		if(0 == exp)\
			_platform_assert();\
	}\
	while (0);
	
#ifndef TRUE
#define TRUE  1
#endif
	
#ifndef FALSE
#define FALSE 0
#endif
	
#ifndef NULL
#define NULL 0
#endif
	
typedef unsigned char  uint8;				
typedef signed	 char  int8;				
typedef unsigned short uint16;				
typedef signed	 short int16;				
typedef unsigned int   uint32;				
typedef signed	 int   int32;				
typedef float		   fp32;				
typedef double		   fp64;				
typedef unsigned char  u_int8;				
typedef unsigned short u_int16; 			
typedef unsigned int   u_int32; 			
	
#if defined (ARMCM33)
  #include "ARMCM33.h"
#elif defined (ARMCM33_TZ)
  #include "ARMCM33_TZ.h"
	
  #if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
    #include "partition_ARMCM33.h"
  #endif
#elif defined (ARMCM33_DSP_FP)
  #include "ARMCM33_DSP_FP.h"
#elif defined (ARMCM33_DSP_FP_TZ)
  #include "ARMCM33_DSP_FP_TZ.h"
	
  #if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
    #include "partition_ARMCM33.h"
  #endif
#elif defined (STAR_CU)
  #include "STAR_CU.h"
#elif defined (STAR_SP)
  #include "STAR_SP.h"
#elif defined (STAR_SE)
  #include "STAR_SE.h"
#else
  #error device not specified!
#endif	

#endif // _PLATFORM_GENERIC_H_
// eof

