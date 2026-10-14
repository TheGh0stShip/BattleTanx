/* libultra 2.0I os/virtualtophysical.c: reconstructed source from decompals/ultralib e24c836
 * (src/os/virtualtophysical.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PRinternal/osint.h"

u32 osVirtualToPhysical(void* addr) {
    if (IS_KSEG0(addr)) {
        return K0_TO_PHYS(addr);
    } else if (IS_KSEG1(addr)) {
        return K1_TO_PHYS(addr);
    } else {
        return __osProbeTLB(addr);
    }
}
