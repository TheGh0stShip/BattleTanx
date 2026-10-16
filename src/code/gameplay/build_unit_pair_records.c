#include "types.h"

typedef struct LinkGroup {
    u8 pad00[8];
    u16 ids[15];
    u16 count;
} LinkGroup;

typedef struct LinkSet {
    LinkGroup a;
    LinkGroup b;
    u8 pad50[2];
} LinkSet;

typedef struct LinkUnit {
    u8 pad000[0x354];
    u8 slot;
} LinkUnit;

typedef struct ByteRecord {
    u8 bytes[12];
} ByteRecord;

extern LinkUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void initialize_byte_record() __asm__("func_800E5688");
extern ByteRecord D_8033AAE8[];
extern u16 D_8033B448;
extern u8 D_8033B450[20][20];
extern s16 D_8033B5E0;

void build_unit_pair_records(s32 n, LinkSet *sets) __asm__("func_800E5328");

void build_unit_pair_records(s32 n, LinkSet *sets)
{
    u16 i;
    u16 j;
    u16 k;
    LinkSet *set;
    LinkGroup *other;
    u16 lo;
    u16 hi;
    u8 *t;
    u8 *tbl;
    u8 c;
    u16 x;
    u16 y;

    D_8033B5E0 = 0;
    D_8033B448 = 0;
    for (i = 0; i < 20; i++) {
        get_unit(i)->slot = i;
    }
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            D_8033B450[i][j] = 0xFF;
        }
    }
    k = 0;
    if (k < (u16)n) {
        tbl = (u8 *)D_8033B450;
loop:
        set = &sets[k];
        other = &set->b;
        for (i = 0; i < set->a.count; i++) {
            for (j = 0; j < set->a.count; j++) {
                if (i != j) {
                    x = set->a.ids[i];
                    y = set->a.ids[j];
                    if ((s16)x < (s16)y) {
                        lo = x;
                        hi = y;
                    } else {
                        lo = y;
                        hi = x;
                    }
                    t = (u8 *)((s16)lo * 20 + (s32)tbl) + (s16)hi;
                    if (*t == 0xFF) {
                        c = D_8033B448;
                        *t = c;
                        initialize_byte_record(&D_8033AAE8[c], (s16)lo, (s16)hi, 1);
                        D_8033B448++;
                    }
                }
            }
        }
        for (i = 0; i < set->a.count; i++) {
            for (j = 0; j < other->count; j++) {
                x = set->a.ids[i];
                y = other->ids[j];
                if ((s16)x < (s16)y) {
                    lo = x;
                    hi = y;
                } else {
                    lo = y;
                    hi = x;
                }
                t = (u8 *)((s16)lo * 20 + (s32)tbl) + (s16)hi;
                if (*t == 0xFF) {
                    c = D_8033B448;
                    *t = c;
                    initialize_byte_record(&D_8033AAE8[c], (s16)lo, (s16)hi, 0);
                    D_8033B448++;
                }
            }
        }
        k++;
        if (k < (u16)n) goto loop;
    }
}
