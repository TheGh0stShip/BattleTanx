/* libultra 2.0I io/vigetcurrframebuf.c: reconstructed source from decompals/ultralib e24c836
 * (src/io/vigetcurrframebuf.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/viint.h"

void* osViGetCurrentFramebuffer(void) {
    register u32 saveMask;
    void* framep;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVIGETCURRENTFRAMEBUFFER, 0);
        return NULL;
    }
#endif

    saveMask = __osDisableInt();
    framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}
