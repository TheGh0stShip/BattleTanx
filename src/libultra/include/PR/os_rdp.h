/* Vendored from decompals/ultralib e24c836 (include/PR/os_rdp.h). */

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)

        $RCSfile: os_rdp.h,v $
        $Revision: 1.1 $
        $Date: 1998/10/09 08:01:16 $
 *---------------------------------------------------------------------*/

#ifndef _OS_RDP_H_
#define	_OS_RDP_H_

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

/* Display processor interface (Dp) */
extern u32 		osDpGetStatus(void);
extern void		osDpSetStatus(u32);
extern void 		osDpGetCounters(u32 *);
extern s32		osDpSetNextBuffer(void *, u64);


#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_RDP_H_ */
