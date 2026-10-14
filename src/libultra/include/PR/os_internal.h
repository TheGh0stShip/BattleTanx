/* Vendored from decompals/ultralib e24c836 (include/PR/os_internal.h). */

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)

        $RCSfile: os_internal.h,v $
        $Revision: 1.20 $
        $Date: 1998/10/09 08:01:09 $
 *---------------------------------------------------------------------*/

#ifndef _OS_INTERNAL_H_
#define	_OS_INTERNAL_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/os.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#include "os_internal_reg.h"
#include "os_internal_exception.h"
#include "os_internal_tlb.h"
#include "os_internal_si.h"
#include "os_internal_rsp.h"
#include "os_internal_error.h"
#include "os_internal_gio.h"
#include "os_internal_thread.h"
#include "os_internal_debug.h"
#include "os_internal_host.h"

#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_INTERNAL_H */
