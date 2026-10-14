#include "types.h"

typedef struct WordRecord {
    u32 words[15];
} WordRecord;

void clear_word_record(WordRecord *record) __asm__("func_80097C24");

void clear_word_record(WordRecord *record)
{
    record->words[0] = 0;
    record->words[1] = 0;
    record->words[2] = 0;
    record->words[5] = 0;
    record->words[6] = 0;
    record->words[8] = 0;
    record->words[3] = 0;
    record->words[4] = 0;
    record->words[7] = 0;
    record->words[11] = 0;
    record->words[12] = 0;
    record->words[9] = 0;
    record->words[10] = 0;
    record->words[13] = 0;
    record->words[14] = 0;
}
