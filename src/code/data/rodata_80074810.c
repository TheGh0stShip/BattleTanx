#include "types.h"

/* Initialized rodata at 0x80074810..0x8007481C (ROM 0x4810..0x481C). */
typedef struct Rodata80074810 {
    f32 value0;
    f32 value4;
    f32 value8;
} Rodata80074810;

const Rodata80074810 D_80074810 = {
    1.0f,
    1.0f,
    1.0f,
};
