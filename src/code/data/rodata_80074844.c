#include "types.h"

/* Initialized rodata at 0x80074844..0x80074850 (ROM 0x4844..0x4850). */
typedef struct Rodata80074844 {
    f32 value0;
    f32 value4;
    f32 value8;
} Rodata80074844;

const Rodata80074844 D_80074844 = {
    1.0f,
    1.0f,
    1.0f,
};
