#include "types.h"

/* Initialized rodata at 0x80074768..0x8007477C (ROM 0x4768..0x477C). */
typedef struct Rodata80074768 {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
    f32 value10;
} Rodata80074768;

const Rodata80074768 D_80074768 = {
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};
