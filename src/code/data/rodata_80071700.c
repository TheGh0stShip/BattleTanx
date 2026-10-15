#include "types.h"

/* Initialized rodata at 0x80071700..0x80071708 (ROM 0x1700..0x1708). */
typedef struct Rodata80071700 {
    f32 value0;
    f32 value4;
} Rodata80071700;

const Rodata80071700 D_80071700 = {
    255.0f,
    2.14748365e+09f,
};
