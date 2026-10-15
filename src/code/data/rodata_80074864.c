#include "types.h"

/* Initialized rodata at 0x80074864..0x8007486C (ROM 0x4864..0x486C). */
typedef struct Rodata80074864 {
    f32 value0;
    f32 value4;
} Rodata80074864;

const Rodata80074864 D_80074864 = {
    1.0f,
    1.0f,
};
