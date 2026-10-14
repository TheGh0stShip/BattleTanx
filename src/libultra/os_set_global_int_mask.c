/* libultra 2.0I os/setglobalintmask.c: reconstructed source from decompals/ultralib e24c836
 * (src/os/setglobalintmask.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "PR/os_internal.h"

void __osSetGlobalIntMask(OSHWIntr mask) {
    register u32 saveMask = __osDisableInt();

    __OSGlobalIntMask |= mask;

    __osRestoreInt(saveMask);
}
