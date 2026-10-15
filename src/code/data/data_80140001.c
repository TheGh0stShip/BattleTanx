#include "types.h"

/* Initialized data at 0x80140001..0x80140002 (ROM 0xD0001..0xD0002). */
typedef struct Data80140001 {
    u8 pad0[1];
} Data80140001;

Data80140001 D_80140001 = {
    { 0x0F },
};
