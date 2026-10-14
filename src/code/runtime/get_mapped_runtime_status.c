#include "types.h"

typedef struct RuntimeTables {
    u8 pad00[0x18];
    u8 *map;
    u8 *status;
} RuntimeTables;

extern RuntimeTables *D_80135834;

u8 get_mapped_runtime_status(u16 index) __asm__("func_800E19DC");

u8 get_mapped_runtime_status(u16 index)
{
    return D_80135834->status[D_80135834->map[index]];
}
