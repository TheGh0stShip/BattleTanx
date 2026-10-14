/* Vendored from decompals/ultralib e24c836 (include/PR/os_cache.h). */

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)

        $RCSfile: os_cache.h,v $
        $Revision: 1.1 $
        $Date: 1998/10/09 08:01:04 $
 *---------------------------------------------------------------------*/

#ifndef _OS_CACHE_H_
#define	_OS_CACHE_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Type definitions
 *
 */


#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

/**************************************************************************
 *
 * Global definitions
 *
 */


#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Macro definitions
 *
 */

#define	OS_DCACHE_ROUNDUP_ADDR(x)	(void *)(((((u32)(x)+0xf)/0x10)*0x10))
#define	OS_DCACHE_ROUNDUP_SIZE(x)	(u32)(((((u32)(x)+0xf)/0x10)*0x10))


/**************************************************************************
 *
 * Extern variables
 *
 */


/**************************************************************************
 *
 * Function prototypes
 *
 */

/* Cache operations and macros */

extern void		osInvalDCache(void *, s32);
extern void		osInvalICache(void *, s32);
extern void		osWritebackDCache(void *, s32);
extern void		osWritebackDCacheAll(void);


#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_CACHE_H_ */
