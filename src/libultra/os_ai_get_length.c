#include "types.h"

u32 osAiGetLength(void) {
    return *(volatile u32*)0xA4500004;
}
