/* libultra 2.0I io/vigetcurrcontext.c: reconstructed source from decompals/ultralib e24c836
 * (src/io/vigetcurrcontext.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "PR/os_internal.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

__OSViContext* __osViGetCurrentContext(void) {
    return __osViCurr;
}
