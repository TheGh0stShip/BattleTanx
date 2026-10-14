#include "types.h"

typedef struct RuntimeTables {
    u8 pad00[0x1C];
    u8 *status;
} RuntimeTables;

extern RuntimeTables *D_80135834;

void clear_runtime_status_byte(u8 index) __asm__("func_800E19B8");

void clear_runtime_status_byte(u8 index)
{
    if (D_80135834 != 0) {
        D_80135834->status[index] = 0;
    }
}
