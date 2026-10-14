#include "types.h"

typedef struct AiFloatContext {
    u8 pad00[8];
    void *store;
} AiFloatContext;

extern s32 ai_get_indexed_float_address(s32 store, s32 index) __asm__("func_800E9880");

s32 ai_get_flagged_float_address(void *context, s32 flags)
    __asm__("func_800E9820");

s32 ai_get_flagged_float_address(void *context, s32 flags)
{
    if (flags & 0x1000) {
        return ai_get_indexed_float_address(*(s32 *)((s8 *)context + 8), flags);
    }
    return 0;
}
