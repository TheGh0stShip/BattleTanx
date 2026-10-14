#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_800A6688(u8);
s32 func_800A6E30(void *, u8);

void release_same_class_effects(void *arg0, void *arg1) __asm__("func_800A7418");

void release_same_class_effects(void *arg0, void *arg1) {
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    void *var_a0;

    if ((*(s32 *)((s8 *)(arg1) + (8))) == 0) {
        temp_s1 = (*(void **)((s8 *)(arg1) + (0xC)));
        temp_s0 = func_800A6688((*(u8 *)((s8 *)(temp_s1) + (4))));
        if ((*(u8 *)((s8 *)(temp_s0) + (0x1AE))) == (*(u8 *)((s8 *)(func_800A6688((*(u8 *)((s8 *)(arg0) + (0xC))))) + (0x1AE)))) {
            var_a0 = (*(void **)((s8 *)(temp_s1) + (0x98)));
            if (var_a0 != NULL) {
                do {
                    temp_s0_2 = (*(void **)((s8 *)(var_a0) + (0x2C)));
                    func_800A6E30(var_a0, (*(u8 *)((s8 *)(arg0) + (0xC))));
                    var_a0 = temp_s0_2;
                } while (var_a0 != NULL);
            }
            (*(void **)((s8 *)(temp_s1) + (0x98))) = NULL;
        }
    }
}
