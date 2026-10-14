/* libc 2.0I sprintf.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */
#include "xstdio.h"
#include "string.h"
#include "os.h"

// TODO: this comes from a header

static void* proutSprintf(void* s, const char* buf, size_t n);

int sprintf(char* s, const char* fmt, ...) {
    int ans;
    va_list ap;
    va_start(ap, fmt);
    ans = _Printf(proutSprintf, s, fmt, ap);
    if (ans >= 0) {
        s[ans] = 0;
    }
    return ans;
}
static void* proutSprintf(void* s, const char* buf, size_t n) {
    return (char*)memcpy(s, buf, n) + n;
}
