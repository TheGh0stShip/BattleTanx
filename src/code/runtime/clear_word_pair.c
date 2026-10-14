#include "types.h"

typedef struct WordPairOwner {
    u8 pad00[0x40];
    u32 first;
    u32 second;
} WordPairOwner;

void clear_word_pair(WordPairOwner *owner) __asm__("func_800E99D4");

void clear_word_pair(WordPairOwner *owner)
{
    owner->first = 0;
    owner->second = 0;
}
