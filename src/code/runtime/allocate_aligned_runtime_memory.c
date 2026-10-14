#include "types.h"

extern s32 D_801C9188;
extern s32 D_801C918C;

s32 allocate_aligned_runtime_memory(s32 size) __asm__("func_80081A78");

s32 allocate_aligned_runtime_memory(s32 size)
{
    s32 result;

    size = (size + 7) & ~7;
    if (D_801C9188 < size) {
        return 0;
    }
    result = D_801C918C;
    D_801C9188 -= size;
    D_801C918C = result + size;
    return result;
}
