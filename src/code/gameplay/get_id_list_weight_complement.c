#include "types.h"

extern f32 D_80074770;
extern f32 D_80074774;

static inline f32 find_id_weight(u16 *list, u16 id) {
    u16 i;

    for (i = 0; i < list[3]; i++) {
        if (id == list[i]) {
            return D_80074770;
        }
    }
    return 0.0f;
}

f32 get_id_list_weight_complement(u16 **listPtr, u16 id) __asm__("func_800E831C");

f32 get_id_list_weight_complement(u16 **listPtr, u16 id) {
    return D_80074774 - find_id_weight(*listPtr, id);
}
