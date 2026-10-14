#include "types.h"
extern volatile s32 D_80147040;
void debug_delay(s32 count) __asm__("func_800760DC");
void debug_delay(s32 count) {
    for (D_80147040 = 0; D_80147040 < count; D_80147040++) {
    }
}
