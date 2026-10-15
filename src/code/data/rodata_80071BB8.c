#include "types.h"

/* Initialized rodata at 0x80071BB8..0x80071BE0 (ROM 0x1BB8..0x1BE0). */
typedef struct Rodata80071BB8 {
    f64 value0;
    f32 value8;
    f32 valueC;
    f32 value10;
    f32 value14;
    f64 value18;
    f32 value20;
    f32 value24;
} Rodata80071BB8;

const Rodata80071BB8 D_80071BB8 = {
    10000.0,
    10.0f,
    5.0f,
    10000000.0f,
    0.0f,
    10000.0,
    35.0f,
    35.0f,
};
