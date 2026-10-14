#include "types.h"

typedef struct RuntimePair {
    u16 first;
    u16 second;
} RuntimePair;

typedef struct RuntimeTables {
    u8 pad00[0x10];
    RuntimePair *pairs;
} RuntimeTables;

extern RuntimeTables *D_80135834;

u16 get_runtime_pair_second(u16 index) __asm__("func_800E0E84");

u16 get_runtime_pair_second(u16 index)
{
    return D_80135834->pairs[index].second;
}
