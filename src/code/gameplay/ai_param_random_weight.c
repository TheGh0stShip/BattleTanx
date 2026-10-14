#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800F3880(f32);
extern f32 D_80074720;

void ai_param_random_weight(void) __asm__("func_800E7734");

void ai_param_random_weight(void) {
    func_800F3880(D_80074720);
}
