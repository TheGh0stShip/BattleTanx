#include "types.h"

typedef struct SortRecord { s32 value00; s32 value04; s32 key; } SortRecord;

#define COPY_RECORD(dst, src) \
    (dst).value04 = (src).value04; \
    (dst).value00 = (src).value00; \
    (dst).key = (src).key

void sort_records_by_key(SortRecord *, s32) __asm__("func_8008C09C");

void sort_records_by_key(SortRecord *records, s32 count)
{
    SortRecord temp;
    SortRecord *low;
    SortRecord *high;
    SortRecord *mid;
    SortRecord *current;
    s32 pivot;
    s32 i;
    s32 j;

    if (count < 2) return;
    if (count == 2) {
        if (records[0].key > records[1].key) {
            COPY_RECORD(temp, records[0]);
            COPY_RECORD(records[0], records[1]);
            COPY_RECORD(records[1], temp);
        }
        return;
    }
    i = 1;
    j = count - 1;
    pivot = records[0].key;
    if (i < j) {
        high = &records[j];
        low = &records[1];
        current = low;
        do {
            if (current->key <= pivot) {
                low = current + 1;
                i++;
            } else {
                current = high;
                if (current->key >= pivot) {
                    high = current - 1;
                    j--;
                } else {
                    COPY_RECORD(temp, *low);
                    low->value04 = high->value04;
                    low->value00 = high->value00;
                    low->key = high->key;
                    high->value04 = temp.value04;
                    high->value00 = temp.value00;
                    high->key = temp.key;
                }
            }
            current = low;
        } while (i < j);
    }
    mid = &records[i];
    if (mid->key < pivot) {
        COPY_RECORD(temp, *mid);
        COPY_RECORD(*mid, records[0]);
        COPY_RECORD(records[0], temp);
        sort_records_by_key(records, i);
        sort_records_by_key(mid + 1, count - i - 1);
    } else {
        COPY_RECORD(temp, mid[-1]);
        COPY_RECORD(mid[-1], records[0]);
        COPY_RECORD(records[0], temp);
        sort_records_by_key(records, i - 1);
        sort_records_by_key(mid, count - i);
    }
}
