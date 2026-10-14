/* libultra 2.0I io/sptaskyield.c: reconstructed source from decompals/ultralib e24c836
 * (src/io/sptaskyield.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "PR/os_internal.h"
#include "PR/rcp.h"

void osSpTaskYield(void) {
    __osSpSetStatus(SP_SET_YIELD);
}
