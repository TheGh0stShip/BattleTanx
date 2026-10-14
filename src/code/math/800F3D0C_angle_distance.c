#include "types.h"

u16 func_800F3D0C(u32 first, u32 second) {
    u32 first16 = first & 0xFFFF;
    u32 second16 = second & 0xFFFF;
    u32 difference;

    if (second16 < first16) {
        difference = first - second;
    } else {
        difference = second - first;
    }
    if ((u16)difference > 0x8000) {
        difference = ~difference;
    }
    return difference;
}
