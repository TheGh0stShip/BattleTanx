/* Vendored from decompals/ultralib e24c836 (include/PR/os_internal_debug.h). */

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)

        $RCSfile: os_internal_debug.h,v $
        $Revision: 1.1 $
        $Date: 1998/10/09 08:01:09 $
 *---------------------------------------------------------------------*/

#ifndef _OS_INTERNAL_DEBUG_H_
#define	_OS_INTERNAL_DEBUG_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/os.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/* Debug port */
extern void		__osSyncPutChars(int, int, const char *);
extern int		__osAtomicDec(unsigned int *p);


#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_INTERNAL_DEBUG_H */
