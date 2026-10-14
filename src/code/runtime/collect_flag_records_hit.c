#include "types.h"

typedef struct FlagRecord {
    u16 mask;
    s16 next;
    u8 pad04[0x4];
    s32 value08;
    u8 shape[0x1C];
} FlagRecord;

extern s32 gFlagRecordHead __asm__("D_803B8240");
extern FlagRecord gFlagRecords[] __asm__("D_803B8248");
extern u8 func_8010A8A8(void *query, void *shape, s32 *out) __asm__("func_8010A8A8");

u8 collect_flag_records_hit(void *query, u16 mask, s32 *values, s32 *count) __asm__("func_80107A14");

u8 collect_flag_records_hit(void *query, u16 mask, s32 *values, s32 *count)
{
    s32 hit;
    s32 n;
    s16 i;

    n = 0;
    for (i = gFlagRecordHead; i != -1; i = gFlagRecords[i].next) {
        if (mask & gFlagRecords[i].mask) {
            if (func_8010A8A8(query, gFlagRecords[i].shape, &hit)) {
                n++;
                *values++ = gFlagRecords[i].value08;
                if (n >= 0x20) {
                    break;
                }
            }
        }
    }
    *count = n;
    return n;
}
