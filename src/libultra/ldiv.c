/* libultra 2.0I libc/ldiv.c: reconstructed source from decompals/ultralib e24c836
 * (src/libc/ldiv.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "os_version.h"
#include "stdlib.h"

// TODO: these come from headers
#ident "$Revision: 1.34 $"
#ident "$Revision: 1.5 $"

ldiv_t ldiv(long num, long denom) {
    ldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot += 1;
        ret.rem -= denom;
    }

    return ret;
}

lldiv_t lldiv(long long num, long long denom) {
    lldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot += 1;
        ret.rem -= denom;
    }

    return ret;
}
