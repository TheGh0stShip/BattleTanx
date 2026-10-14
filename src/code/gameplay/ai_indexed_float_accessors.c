#include "types.h"

typedef struct AiFloatStore {
    u8 pad000[0x10C];
    f32 values[256];
} AiFloatStore;

f32 ai_get_indexed_float(AiFloatStore *store, u8 index) __asm__("func_800E9854");
void ai_set_indexed_float(AiFloatStore *store, u8 index, f32 value) __asm__("func_800E986C");
f32 *ai_get_indexed_float_address(AiFloatStore *store, u8 index) __asm__("func_800E9880");

f32 ai_get_indexed_float(AiFloatStore *store, u8 index)
{
    return store->values[index];
}

void ai_set_indexed_float(AiFloatStore *store, u8 index, f32 value)
{
    store->values[index] = value;
}

f32 *ai_get_indexed_float_address(AiFloatStore *store, u8 index)
{
    return &store->values[index];
}
