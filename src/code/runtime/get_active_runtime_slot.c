#include "types.h"

extern s32 D_80137900;
extern void *D_8033B610[];

void *get_active_runtime_slot(s32 index) __asm__("func_800ECB68");

void *get_active_runtime_slot(s32 index)
{
    void *result;

    if (D_80137900 != 0) {
        result = D_8033B610[index];
    } else {
        result = 0;
    }
    return result;
}
