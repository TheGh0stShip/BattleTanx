#include "types.h"

u16 previous_index_in_triple(u16 index) __asm__("func_800E0E1C");

u16 previous_index_in_triple(u16 index) {
    u16 group = index / 3;
    u16 slot = index % 3;

    return (slot + 2) % 3 + group * 3;
}
