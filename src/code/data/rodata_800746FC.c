#include "types.h"

/* Initialized rodata at 0x800746FC..0x80074700 (ROM 0x46FC..0x4700). */
typedef struct Rodata800746FC {
    f32 value0;
} Rodata800746FC;

const Rodata800746FC D_800746FC = {
    1000.0f,
};
