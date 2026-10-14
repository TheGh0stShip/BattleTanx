#include "types.h"

void alCopy(void* source, void* destination, s32 length) {
    u8* src = source;
    u8* dst = destination;
    s32 i;

    for (i = 0; i < length; i++) {
        *dst++ = *src++;
    }
}
