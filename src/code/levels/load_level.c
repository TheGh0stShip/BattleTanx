#include "types.h"

typedef struct PlayerColorInfo {
    u8 pad00[0x3D];
    u8 color;
} PlayerColorInfo;

extern s32 D_80125850;
extern u8 D_80125854;
extern s32 D_80125858;
extern f32 D_8012585C;
extern u8 D_80135775;
extern u8 D_80135776;
extern s32 D_801C9170;
extern s32 D_801C9174;
extern s32 D_801C9178;
extern s32 D_801C9188;
extern u8 *D_801C918C;
extern s16 D_802D5A30[182];
extern u8 D_803DA800[];

extern s32 get_view_count(void) __asm__("func_8007AAA0");
extern s32 func_800EC644(void);
extern s32 func_800EC3D0(void);
extern void func_800DDA08(s32 size, void *buffer, s32 level);
extern s32 func_800ECB68(s32 index);
extern PlayerColorInfo *func_800A68C0(s32 player);
extern s32 func_800805C0(void);
extern s32 func_800805D0(void);
extern s32 func_80088CF0(s32 level, u8 *heap, s32 heapSize, void *buffer, s32 bufferSize, s32 arg5, s32 arg6,
                         s32 *players);
extern void func_8010BC08(void);
extern void func_80085460(void);
extern void func_80085468(void);
extern s32 func_80086AE8(void);
extern void func_8008C8D0(f32 x, f32 z, s32 arg2);
extern void func_8008B080(void);

static inline u8 *heap_alloc(s32 size)
{
    u8 *ptr;

    if (D_801C9188 < size) {
        return 0;
    }
    D_801C9188 -= size;
    ptr = D_801C918C;
    D_801C918C += size;
    return ptr;
}

static inline void enable_color_models(PlayerColorInfo *info)
{
    D_802D5A30[129 + info->color] = 0;
    D_802D5A30[119 + info->color] = 0;
    D_802D5A30[99 + info->color] = 0;
    D_802D5A30[109 + info->color] = 0;
    D_802D5A30[169 + info->color] = 0;
    D_802D5A30[139 + info->color] = 0;
    D_802D5A30[149 + info->color] = 0;
}

void load_level(s32 level, s32 *players) __asm__("func_80081AD0");

void load_level(s32 level, s32 *players)
{
    PlayerColorInfo *info;
    u8 *buffer;
    s32 i;
    s32 used;
    s32 extent;

    D_80125850 = level;
    switch (get_view_count()) {
    case 3:
    case 4:
        D_8012585C = 2.2f;
        break;
    case 2:
        D_8012585C = 1.12f;
        break;
    case 1:
        if (func_800EC644() != 0 && func_800EC3D0() != 0) {
            D_8012585C = 1.12f;
        } else {
            D_8012585C = 2.29f;
        }
        break;
    }
    buffer = heap_alloc(40000);
    if (buffer == 0) {
        return;
    }
    func_800DDA08(40000, buffer, level);
    for (i = 0; i < 182; i++) {
        D_802D5A30[i] = -1;
    }
    D_802D5A30[0] = -1;
    D_802D5A30[1] = 0;
    D_802D5A30[2] = 0;
    D_802D5A30[3] = 0;
    D_802D5A30[4] = -1;
    D_802D5A30[5] = -1;
    D_802D5A30[6] = -1;
    D_802D5A30[7] = -1;
    D_802D5A30[9] = 0;
    D_802D5A30[10] = 0;
    D_802D5A30[8] = -1;
    D_802D5A30[11] = 0;
    D_802D5A30[12] = 0;
    D_802D5A30[13] = 0;
    D_802D5A30[14] = 0;
    D_802D5A30[15] = 0;
    D_802D5A30[16] = 0;
    D_802D5A30[17] = 0;
    D_802D5A30[18] = 0;
    D_802D5A30[19] = 0;
    D_802D5A30[20] = 0;
    D_802D5A30[21] = 0;
    D_802D5A30[22] = 0;
    D_802D5A30[23] = 0;
    D_802D5A30[25] = 0;
    D_802D5A30[26] = 0;
    D_802D5A30[27] = 0;
    D_802D5A30[28] = 0;
    D_802D5A30[29] = 0;
    D_802D5A30[30] = 0;
    D_802D5A30[31] = 0;
    D_802D5A30[32] = 0;
    D_802D5A30[33] = 0;
    D_802D5A30[34] = 0;
    D_802D5A30[35] = 0;
    D_802D5A30[36] = 0;
    D_802D5A30[37] = 0;
    D_802D5A30[38] = 0;
    D_802D5A30[39] = 0;
    D_802D5A30[40] = 0;
    D_802D5A30[41] = 0;
    D_802D5A30[42] = 0;
    D_802D5A30[43] = 0;
    D_802D5A30[44] = 0;
    D_802D5A30[45] = 0;
    D_802D5A30[46] = 0;
    D_802D5A30[47] = 0;
    D_802D5A30[92] = 0;
    D_802D5A30[93] = 0;
    D_802D5A30[94] = 0;
    D_802D5A30[95] = 0;
    D_802D5A30[62] = 0;
    D_802D5A30[63] = 0;
    D_802D5A30[64] = 0;
    D_802D5A30[66] = 0;
    D_802D5A30[68] = 0;
    D_802D5A30[23] = 0;
    D_802D5A30[65] = 0;
    D_802D5A30[67] = 0;
    D_802D5A30[72] = 0;
    D_802D5A30[69] = 0;
    D_802D5A30[70] = 0;
    D_802D5A30[71] = 0;
    D_802D5A30[73] = 0;
    D_802D5A30[79] = 0;
    D_802D5A30[80] = 0;
    D_802D5A30[76] = 0;
    D_802D5A30[77] = 0;
    D_802D5A30[78] = 0;
    D_802D5A30[82] = 0;
    D_802D5A30[83] = 0;
    D_802D5A30[84] = 0;
    D_802D5A30[85] = 0;
    D_802D5A30[86] = 0;
    D_802D5A30[87] = 0;
    D_802D5A30[88] = 0;
    D_802D5A30[89] = 0;
    D_802D5A30[90] = 0;
    D_802D5A30[97] = 0;
    D_802D5A30[98] = 0;
    if (D_80135775 != 0 || D_80135776 != 0) {
        D_802D5A30[24] = 0;
    }
    if (level == 16) {
        D_802D5A30[179] = 0;
    }
    if (func_800EC644() != 0) {
        D_802D5A30[180] = 0;
        D_802D5A30[181] = 0;
        for (i = 0; i < 2; i++) {
            info = func_800A68C0(func_800ECB68(i));
            if (info->color != 0xFF) {
                enable_color_models(info);
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            info = func_800A68C0(players[i]);
            if (info->color != 0xFF) {
                enable_color_models(info);
            }
        }
    }
    D_801C9170 = (s32)D_801C918C;
    used = func_80088CF0(level, D_801C918C, D_801C9188, D_803DA800, 0x25800, func_800805C0(),
                         func_800805D0(), players);
    if (used >= 0) {
        func_8010BC08();
        if (D_80125854 != 0) {
            func_80085460();
        } else {
            func_80085468();
        }
        D_801C918C += used;
        D_801C9188 -= used;
        extent = (s16)func_80086AE8();
        D_80125858 = extent;
        D_801C9178 = extent;
        D_801C9174 = extent * extent;
        if (D_80135775 != 0) {
            func_8008C8D0(0.0f, 0.0f, 0);
        }
        func_8008B080();
    }
}
