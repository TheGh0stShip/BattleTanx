#include "types.h"

typedef struct MinimumCandidate {
    s32 value;
    void *owner;
} MinimumCandidate;

void update_minimum_candidate(void *owner, s32 value, MinimumCandidate *best)
    __asm__("func_800949B8");

void update_minimum_candidate(void *owner, s32 value, MinimumCandidate *best)
{
    s32 isSmaller;

    isSmaller = best->value;
    isSmaller = value < isSmaller;
    if (isSmaller) {
        best->value = value;
        best->owner = owner;
    }
}
