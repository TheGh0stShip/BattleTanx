#include "types.h"

/* Initialized rodata at 0x80074870..0x80074884 (ROM 0x4870..0x4884). */
typedef struct Rodata80074870 {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
    f32 value10;
} Rodata80074870;

const Rodata80074870 D_80074870 = {
    3.9999999e-05f,
    1.0f,
    1.0f,
    3.9999999e-05f,
    1.0f,
};
