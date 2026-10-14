#include "types.h"

s32 func_80076CA8(u8 *text) {
    u8 *end = text;

    while (*end++ != 0) {
    }
    return end - text;
}
