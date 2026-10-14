#include "types.h"

typedef union Gfx {
    struct {
        u32 w0;
        u32 w1;
    } words;
    u64 alignment;
} Gfx;

#define OPENING_GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->words.w0 = (first); \
    command->words.w1 = (second); \
}
#define gDPPipeSync(packet) OPENING_GFX_COMMAND(packet, 0xE7000000U, 0)
#define gDPSetCycleType(packet, type) OPENING_GFX_COMMAND(packet, 0xBA001402U, type)
#define gDPSetCombineLERP(packet, a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0, \
                         a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1) \
    OPENING_GFX_COMMAND(packet, 0xFCFFFFFFU, 0xFFFCF279U)
#define gDPSetRenderMode(packet, first, second) \
    OPENING_GFX_COMMAND(packet, 0xB900031DU, (first) | (second))
#define gDPSetTexturePersp(packet, type) OPENING_GFX_COMMAND(packet, 0xBA001301U, type)
#define gDPSetTextureLOD(packet, type) OPENING_GFX_COMMAND(packet, 0xBA001001U, type)
#define gDPSetTextureFilter(packet, type) OPENING_GFX_COMMAND(packet, 0xBA000C02U, type)
#define gDPSetTextureConvert(packet, type) OPENING_GFX_COMMAND(packet, 0xBA000903U, type)
#define gDPSetTextureLUT(packet, type) OPENING_GFX_COMMAND(packet, 0xBA000E02U, type)

#define G_CYC_1CYCLE 0
#define G_TP_NONE 0
#define G_TL_TILE 0
#define G_TF_POINT 0
#define G_TC_FILT 0xC00
#define G_TT_RGBA16 0x8000

int func_800798C0(int);
void func_80079BB4(int);
int func_80079BD4(void);
void func_80079BF4(int);
int func_800AD340(void);
int func_800AD5A0(void);
void func_800AD828(void);
void func_800ADD70(void);
void func_800AE2B8(void);
int func_800AE800(void);
void func_800AEA50(void);
void func_800AEF98(void);
int func_800AF534(void);
int func_800AFB08(void);
int func_800B0210(void);
void func_800B0440(void);
void func_800B098C(void);
void func_800B0D1C(void);
int func_800B1264(void);
int func_800B9C0C(void *);
int func_800B9C34(int, int);
int func_800F4DFC(Gfx **, int, int, int, int, int, int, int, int);
void func_801054E0(int);
void func_8010552C(int, int);
void func_8010555C(int, int, int, int);
void func_80105A50(Gfx **, char *, int, int);
void func_8010698C(Gfx **);
u64 func_801120A0(void);

extern u64 D_80145DA0;
extern char D_800731C0[];
extern char D_800731CC[];
extern s32 D_80125794;
extern char D_801326C4[];
extern char D_80132704[];
extern char D_8013273C[];
extern char D_80132754[];
extern char D_801329C8[];
extern char D_80132A04[];
extern char D_80132A34[];
extern char D_80132A78[];
extern char D_80132AA8[];
extern u8 D_803276E1;
extern s32 D_803276F0;
extern s32 D_80327708;
extern u8 D_8032770C;
extern s32 D_80327718;
extern s32 D_80327730;
extern s32 D_80327734;
extern s32 D_80327760;
extern s32 D_80327764;
extern s32 D_80327790;
extern u8 D_80327794;
extern u8 D_80327795;
extern u8 D_80327796;
extern u8 D_803277C8;
extern u8 D_803277C9;
extern u8 D_803277CA;
extern u8 D_803277CB;
extern s32 D_803277CC;
extern s32 D_803277DC;
extern u8 D_80327808;
extern u8 D_80327809;
extern u8 D_8032780A;
extern u8 D_8032780B;
extern s32 D_8032780C;
extern s32 D_80327810;
extern s32 D_80327814;
extern s32 D_80327818;
extern u8 D_80327848;
extern u8 D_80327849;
extern u8 D_8032784A;
extern u8 D_8032784B;
extern s32 D_8032784C;
extern s32 D_80327850;
extern s32 D_80327854;
extern s32 D_80327858;
extern s32 D_80327878;
extern s32 D_8032787C;
extern s32 D_80327880;
extern u8 D_803278B8;
extern u8 D_803278B9;
extern u8 D_803278BA;
extern u8 D_803278BB;
extern s32 D_803278BC;
extern s32 D_803278D8;
extern s32 D_803278F0;
extern s32 D_803278F4;
extern s32 D_803278F8;
extern u8 D_80327920;
extern u8 D_80327921;
extern u8 D_80327922;
extern u8 D_80327923;
extern s32 D_80327948;
extern s32 D_8032794C;
extern s32 D_80327950;
extern u8 D_80327970;
extern u8 D_80327971;
extern u8 D_80327972;
extern s32 D_80327974;
extern s32 D_80327978;
extern u8 D_803279D8;
extern u8 D_803279D9;
extern u8 D_803279DA;
extern u8 D_803279DB;
extern u8 D_803279DC;
extern s32 D_803279E0;
extern s32 D_803279E4;
extern u8 D_803279E8;
extern u8 D_803279E9;
extern s32 D_80327A08;
extern s32 D_80327A0C;
extern s32 D_80327A10;
extern u64 D_80327A38;
extern s32 D_80327A50;
extern s32 D_80327A68;
extern s32 D_80327A6C;
extern s32 D_80327A70;
extern u8 D_80327A90;
extern u8 D_80327A91;
extern u8 D_80327A92;
extern u8 D_80327AA0;
extern u8 D_80327AA1;
extern s32 D_80327AB0;
extern u8 D_80327AD8;
extern u8 D_80327AD9;
extern u8 D_80327ADA;
extern s32 D_80327AF8;
extern s32 D_80327AFC;
extern s32 D_80327B00;
extern s32 D_80327B04;
extern s32 D_80327B08;
extern u8 D_80327B22;
extern u8 D_80327B23;
extern u8 D_80327B24;
extern s32 D_80327B30;
extern s32 D_80327B38;
extern u64 D_80327B28;
extern u64 D_80327AE8;
extern u64 D_80327AC0;
extern u64 D_80327B18;
extern u64 D_80327AD0;
extern u64 D_80327AF0;
extern u64 D_80327B10;
extern u64 D_80327AC8;
extern u64 D_803279F0;
extern u64 D_80327A20;
extern u64 D_80327990;
extern u64 D_80327A98;
extern u64 D_80327A28;
extern u64 D_80327AB8;
extern u64 D_80327A00;
extern u64 D_80327700;
extern u64 D_80327AA8;
extern u64 D_803279F8;
extern u64 D_803276E8;
extern u64 D_80327AE0;
extern u64 D_80327988;
extern u64 D_803276F8;
extern u64 D_80327A18;
extern u64 D_803277B8;
extern u64 D_803279B0;
extern u64 D_803278B0;
extern u64 D_80327840;
extern u64 D_80327770;
extern u64 D_803279A8;
extern u64 D_80327958;
extern u64 D_80327930;
extern u64 D_803278A0;
extern u64 D_80327828;
extern u64 D_80327798;
extern u64 D_80327740;
extern u64 D_80327870;
extern u64 D_80327758;
extern u64 D_803279D0;
extern u64 D_803279C8;
extern u64 D_803279B8;
extern u64 D_80327838;
extern u64 D_80327968;
extern u64 D_80327750;
extern u64 D_80327778;
extern u64 D_80327780;
extern u64 D_80327980;
extern u64 D_80327868;
extern u64 D_80327820;
extern u64 D_80327830;
extern u64 D_803278A8;
extern u64 D_803277B0;
extern u64 D_80327998;
extern u64 D_803279A0;
extern u64 D_80327860;
extern u64 D_80327890;
extern u64 D_803277A8;
extern u64 D_80327748;
extern u64 D_80327788;
extern u64 D_80327928;
extern u64 D_80327940;
extern u64 D_803277C0;
extern u64 D_80327888;
extern u64 D_80327898;
extern u64 D_80327938;
extern u64 D_80327768;
extern u64 D_80327960;
extern u64 D_803279C0;
extern u64 D_80327720;
extern u64 D_80327710;
extern u64 D_80327728;
extern u64 D_80327738;
extern u64 D_80327800;
extern u64 D_803277E8;
extern u64 D_803277F0;
extern u64 D_803277F8;
extern u64 D_80327918;
extern u64 D_803278E8;
extern u64 D_80327A60;
extern u64 D_803277E0;
extern u64 D_803278E0;
extern u64 D_80327900;
extern u64 D_80327908;
extern u64 D_80327910;
extern u64 D_80327A58;
extern u64 D_80327A78;
extern u64 D_80327A80;
extern u64 D_80327A88;
extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern u8 gOpeningSequencePhase __asm__("D_803276E0");
extern u8 gOpeningSequenceFinished __asm__("D_80327B20");
extern u8 gOpeningSequenceSkipRequested __asm__("D_80327B21");
extern s32 gOpeningSequenceAudioHandle __asm__("D_80327B34");

void render_opening_sequence(void) __asm__("func_800B1520");

const f32 gOpeningSequenceScale __asm__("D_80073210") = 1.0f;

void render_opening_sequence(void) {
    char *captionText;
    u64 currentTime;
    u64 timeDelta;
    f32 transitionRatio;
    f32 fadeAlpha;
    f32 deltaAsFloat;
    s32 temp_f2_11;
    s32 temp_f2_14;
    s32 temp_f2_15;
    s32 temp_f2_18;
    s32 temp_f2_4;
    s32 temp_f2_5;
    s32 temp_f2_6;
    s32 temp_f2_7;
    s32 temp_f2_8;
    s32 temp_f2_9;
    u64 temp_ret_102;
    u64 temp_ret_120;
    u64 temp_ret_122;
    u64 temp_ret_132;
    u64 temp_ret_142;
    u64 temp_ret_14;
    u64 temp_ret_28;
    u64 temp_ret_38;
    u64 temp_ret_48;
    u64 temp_ret_58;
    u64 temp_ret_66;
    u64 temp_ret_80;
    s32 var_a0;
    s32 var_a0_10;
    s32 var_a0_11;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_a0_7;
    s32 var_a0_8;
    s32 var_a0_9;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v1_4;

    func_800F4DFC(&gFrontendDisplayList, 0, 0, 0x140, 0xF0, 0, 0, 0, 0xFF);
    gDPPipeSync(gFrontendDisplayList++);
    gDPSetCycleType(gFrontendDisplayList++, G_CYC_1CYCLE);
    gDPSetCombineLERP(gFrontendDisplayList++, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0);
    gDPSetRenderMode(gFrontendDisplayList++, 0x0F0A4000, 0);
    gDPSetTexturePersp(gFrontendDisplayList++, G_TP_NONE);
    gDPSetTextureLOD(gFrontendDisplayList++, G_TL_TILE);
    gDPSetTextureFilter(gFrontendDisplayList++, G_TF_POINT);
    gDPSetTextureConvert(gFrontendDisplayList++, G_TC_FILT);
    gDPSetTextureLUT(gFrontendDisplayList++, G_TT_RGBA16);
    currentTime = (func_801120A0() * 1000000ULL / D_80145DA0);
    func_801054E0(3);
    switch ((u8) gOpeningSequencePhase) {
    case 0x0:
        if (D_803276E8 < currentTime) {
            D_803276E1 = 0xFF;
        } else {
            timeDelta = D_803276E8 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            transitionRatio = 1.0f - transitionRatio;
            fadeAlpha = transitionRatio * 255.0f;
            D_803276E1 = (u8) fadeAlpha;
        }
        if (D_80327700 < currentTime) {
            timeDelta = currentTime - D_80327700;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            D_80327708 = (s32) (transitionRatio * 255.0f);
        }
        if (D_803276F8 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 1;
        D_80327730 = 0;
        D_8032770C = 0xFF;
        D_80327718 = 0;
        D_80327720 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xE4E1C0ULL;
        D_80327710 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_80327728 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
        func_80079BD4();
        func_80079BB4(0xE);
        func_80079BF4((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            func_8010698C(&gFrontendDisplayList);
            func_8010555C(0xC8, 0xC8, 0xC8, D_803276E1);
            func_8010552C(0, 0x46);
            func_80105A50(&gFrontendDisplayList, D_800731C0, 0, 0x140);
            func_800F4DFC(&gFrontendDisplayList, 0, 0, 0x140, 0xF0, 0, 0, 0, D_80327708);
            return;
        }
    case 0x1:
        if (D_80327710 < currentTime) {
            D_8032770C = 0xFF;
        } else {
            timeDelta = D_80327710 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 3000000.0f;
            transitionRatio = 1.0f - transitionRatio;
            fadeAlpha = transitionRatio * 255.0f;
            D_8032770C = (u8) fadeAlpha;
        }
        if (D_80327728 < currentTime) {
            timeDelta = currentTime - D_80327728;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 3000000.0f;
            D_80327730 = (s32) (transitionRatio * 255.0f);
        }
        if (D_80327720 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 2;
        D_80327740 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x4C4B40ULL;
        D_80327748 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        temp_ret_14 = func_801120A0();
        D_80327760 = 0;
        temp_ret_14 = temp_ret_14 * 1000000ULL / D_80145DA0;
        D_80327750 = temp_ret_14 + 0x1E8480ULL;
        D_80327764 = 0xFF;
        D_80327758 = (func_801120A0() * 1000000ULL / D_80145DA0);
        func_80079BD4();
        func_80079BB4(0xD);
        func_80079BF4((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            func_800AD340();
            return;
        }
    case 0x2:
        if (currentTime >= D_80327750) {
            D_80327764 = 0;
        } else {
            timeDelta = D_80327750 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            D_80327764 = (s32) (transitionRatio * 255.0f);
        }
        if (D_80327740 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 3;
        D_80327790 = 0;
        D_80327768 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_80327778 = (func_801120A0() * 1000000ULL / D_80145DA0);
        D_80327780 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_80327788 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        temp_ret_28 = func_801120A0();
        D_80327734 = 0;
        D_80327796 = 0;
        D_80327795 = 0;
        D_80327794 = 0;
        temp_ret_28 = temp_ret_28 * 1000000ULL / D_80145DA0;
        D_80327770 = temp_ret_28 + 0x5B8D80ULL;
        return;
        } else {
            if (D_80327748 < currentTime) {
                timeDelta = currentTime - D_80327748;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                D_80327760 = (s32) (transitionRatio * 255.0f);
            }
            if (D_80327758 < currentTime) {
                D_80327758 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xF4240ULL;
                func_800B9C34(0x29, 0x3800);
            }
            {
                u64 unused_delta = D_80327738 - currentTime;
                D_80327B28 = unused_delta;
                deltaAsFloat = (f32) unused_delta;
            }
            func_800AD5A0();
            return;
        }
    case 0x3:
        if (D_80327768 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 4;
        D_803277CC = 0;
        D_80327798 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_803277A8 = (func_801120A0() * 1000000ULL / D_80145DA0);
        D_803277B0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_803277B8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        temp_ret_38 = func_801120A0();
        D_803277CB = 0;
        D_803277CA = 0;
        D_803277C9 = 0;
        D_803277C8 = 0;
        D_803277DC = 0;
        temp_ret_38 = temp_ret_38 * 1000000ULL / D_80145DA0;
        D_803277C0 = temp_ret_38 + 0x5B8D80ULL;
        gOpeningSequenceFinished = 1;
        D_80327B22 = 1;
        func_80079BD4();
        func_80079BB4(8);
        func_80079BF4((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            if (D_80327778 < currentTime) {
                D_80327794 = 0xFF;
            }
            if (D_80327780 < currentTime) {
                D_80327790 = 1;
                D_80327795 = 0xFF;
            }
            if (D_80327788 < currentTime) {
                D_80327790 = 2;
                D_80327796 = 0xFF;
            }
            if (D_80327770 < currentTime) {
                timeDelta = currentTime - D_80327770;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                D_80327734 = (s32) (transitionRatio * 255.0f);
                transitionRatio = (f32) (1.0 - (f64) transitionRatio);
                func_80079BF4((s32) (s16) (s32) (transitionRatio * (f32) (D_80125794 << 0xC)));
            }
            func_800AD828();
            return;
        }
    case 0x5:
        if (D_803277E0 < currentTime || (gOpeningSequenceSkipRequested != 0)) {
            D_80327820 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
            D_80327828 = (func_801120A0() * 1000000ULL / D_80145DA0);
            D_80327830 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x3D0900ULL;
            D_80327838 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x7A1200ULL;
            temp_ret_48 = func_801120A0();
            D_80327849 = 0;
            D_8032784A = 0;
            D_8032784B = 0;
            temp_ret_48 = temp_ret_48 * 1000000ULL / D_80145DA0;
            D_80327840 = temp_ret_48 + 0x895440ULL;
            D_80327848 = 0xFF;
            D_80327850 = func_800B9C0C(D_801326C4);
            D_80327854 = func_800B9C0C(D_80132704);
            D_80327858 = func_800B9C0C(D_8013273C);
            gOpeningSequencePhase = 6;
            D_8032784C = 0;
            D_80327B30 = 0;
            if (D_80327B38 != -1) {
                func_800798C0(D_80327B38);
                D_80327B38 = -1;
            }
            if (gOpeningSequenceAudioHandle != -1) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
            func_800B9C34(0x27, 0x7000);
            D_80327B38 = func_800B9C34(0x28, 0x7000);
            gOpeningSequenceAudioHandle = func_800B9C34(0x24, 0x7000);
            return;
        }
        if (D_80327800 < currentTime) {
            timeDelta = currentTime - D_80327800;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 3000000.0f;
            fadeAlpha = transitionRatio * 255.0f;
            D_8032780B = (u8) fadeAlpha;
        }
        if (D_803277E8 < currentTime) {
            D_80327808 = 0xFF;
            timeDelta = currentTime - D_803277E8;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_2 = D_80327810;
            temp_f2_4 = (s32) (deltaAsFloat / 66666.0f);
            D_80327B30 = temp_f2_4;
            if (temp_f2_4 < var_a0_2) {
                var_a0_2 = temp_f2_4;
            }
            D_80327B30 = var_a0_2;
            if ((D_8032780C == 0) && (var_a0_2 == D_80327810) && (gOpeningSequenceAudioHandle != -1)) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
            var_v0 = D_80327B30;
            if (var_v0 <= 0) {
                var_v0 = 1;
            }
            D_80327B30 = var_v0;
        }
        if (D_803277F0 < currentTime) {
            if (D_8032780C == 0) {
                gOpeningSequenceAudioHandle = func_800B9C34(0x24, 0x7000);
                D_8032780C = 1;
            }
            D_80327809 = 0xFF;
            timeDelta = currentTime - D_803277F0;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_3 = D_80327814;
            temp_f2_5 = (s32) (deltaAsFloat / 66666.0f);
            D_80327B30 = temp_f2_5;
            if (temp_f2_5 < var_a0_3) {
                var_a0_3 = temp_f2_5;
            }
            D_80327B30 = var_a0_3;
            if ((D_8032780C == 1) && (var_a0_3 == D_80327814) && (gOpeningSequenceAudioHandle != -1)) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
            var_v0_2 = D_80327B30;
            if (var_v0_2 <= 0) {
                var_v0_2 = 1;
            }
            D_80327B30 = var_v0_2;
        }
        if (D_803277F8 < currentTime) {
            if (D_8032780C == 1) {
                gOpeningSequenceAudioHandle = func_800B9C34(0x24, 0x7000);
            }
            D_8032780C = 2;
            D_8032780A = 0xFF;
            timeDelta = currentTime - D_803277F8;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_4 = D_80327818;
            temp_f2_6 = (s32) (deltaAsFloat / 66666.0f);
            D_80327B30 = temp_f2_6;
            if (temp_f2_6 < var_a0_4) {
                var_a0_4 = temp_f2_6;
            }
            D_80327B30 = var_a0_4;
            if ((var_a0_4 == D_80327818) && (gOpeningSequenceAudioHandle != -1)) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
            var_v0_3 = D_80327B30;
            if (var_v0_3 <= 0) {
                var_v0_3 = 1;
            }
            D_80327B30 = var_v0_3;
        }
        func_800ADD70();
        return;
    case 0x6:
        if (D_80327820 < currentTime || (gOpeningSequenceSkipRequested != 0)) {
            D_80327868 = (func_801120A0() * 1000000ULL / D_80145DA0);
            D_80327860 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x4C4B40ULL;
            D_80327870 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            D_80327878 = func_800B9C0C(D_80132754);
            gOpeningSequencePhase = 7;
            if (gOpeningSequenceAudioHandle != -1) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
            if (D_80327B38 != -1) {
                func_800798C0(D_80327B38);
                D_80327B38 = -1;
            }
            func_80079BD4();
            func_80079BB4(0xD);
            func_80079BF4((s32) (s16) (D_80125794 << 0xC));
            return;
        }
        if (D_80327828 < currentTime) {
            D_80327848 = 0xFF;
            timeDelta = currentTime - D_80327828;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_5 = D_80327850;
            temp_f2_7 = (s32) (deltaAsFloat / 66666.0f);
            D_80327B30 = temp_f2_7;
            if (temp_f2_7 < var_a0_5) {
                var_a0_5 = temp_f2_7;
            }
            D_80327B30 = var_a0_5;
            var_v1_4 = var_a0_5;
            if (var_v1_4 <= 0) {
                var_v1_4 = 1;
            }
            D_80327B30 = var_v1_4;
            if ((D_8032784C == 0) && (var_v1_4 == D_80327850) && (gOpeningSequenceAudioHandle != -1)) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
        }
        if (D_80327830 < currentTime) {
            if (D_8032784C == 0) {
                func_800B9C34(0x27, 0x7000);
                gOpeningSequenceAudioHandle = func_800B9C34(0x24, 0x7000);
                D_8032784C = 1;
            }
            D_80327849 = 0xFF;
            timeDelta = currentTime - D_80327830;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_6 = D_80327854;
            temp_f2_8 = (s32) (deltaAsFloat / 66666.0f);
            D_80327B30 = temp_f2_8;
            if (temp_f2_8 < var_a0_6) {
                var_a0_6 = temp_f2_8;
            }
            D_80327B30 = var_a0_6;
            if (var_a0_6 <= 0) {
                var_a0_6 = 1;
            }
            D_80327B30 = var_a0_6;
            if ((D_8032784C == 1) && (var_a0_6 == D_80327854) && (gOpeningSequenceAudioHandle != -1)) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
        }
        if (D_80327838 < currentTime) {
            if (D_8032784C == 1) {
                if (D_80327B38 != -1) {
                    func_800798C0(D_80327B38);
                    D_80327B38 = -1;
                }
                gOpeningSequenceAudioHandle = func_800B9C34(0x24, 0x7000);
                D_8032784C = 2;
            }
            D_8032784A = 0xFF;
            timeDelta = currentTime - D_80327838;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_7 = D_80327858;
            temp_f2_9 = (s32) (deltaAsFloat / 66666.0f);
            D_80327B30 = temp_f2_9;
            if (temp_f2_9 < var_a0_7) {
                var_a0_7 = temp_f2_9;
            }
            D_80327B30 = var_a0_7;
            if (var_a0_7 <= 0) {
                var_a0_7 = 1;
            }
            D_80327B30 = var_a0_7;
            if ((D_8032784C == 2) && (var_a0_7 == D_80327858) && (gOpeningSequenceAudioHandle != -1)) {
                func_800798C0(gOpeningSequenceAudioHandle);
                gOpeningSequenceAudioHandle = -1;
            }
        }
        if (D_80327840 < currentTime) {
            timeDelta = currentTime - D_80327840;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 3000000.0f;
            fadeAlpha = transitionRatio * 255.0f;
            D_8032784B = (u8) fadeAlpha;
        }
        func_800AE2B8();
        return;
    case 0x7:
        if (D_80327860 < currentTime || (gOpeningSequenceSkipRequested != 0)) {
            D_80327890 = (func_801120A0() * 1000000ULL / D_80145DA0);
            temp_ret_58 = func_801120A0();
            D_803278BC = 0;
            temp_ret_58 = temp_ret_58 * 1000000ULL / D_80145DA0;
            D_80327888 = temp_ret_58 + 0x895440ULL;
            gOpeningSequencePhase = 8;
            D_80327898 = (func_801120A0() * 1000000ULL / D_80145DA0);
            D_803278A0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            D_803278A8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
            temp_ret_66 = func_801120A0();
            D_803278B9 = 0;
            D_803278BA = 0;
            temp_ret_66 = temp_ret_66 * 1000000ULL / D_80145DA0;
            D_803278B0 = temp_ret_66 + 0x5B8D80ULL;
            D_803278B8 = 0xFF;
            return;
        }
        if (D_80327870 < currentTime) {
            D_80327880 = 0;
        } else {
            timeDelta = D_80327870 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 3000000.0f;
            D_80327880 = (s32) (transitionRatio * 255.0f);
        }
        timeDelta = currentTime - D_80327868;
        D_80327B28 = timeDelta;
        deltaAsFloat = (f32) timeDelta;
        var_a0_8 = D_80327878;
        temp_f2_11 = (s32) (deltaAsFloat / 66666.0f);
        D_8032787C = temp_f2_11;
        if (temp_f2_11 < var_a0_8) {
            var_a0_8 = temp_f2_11;
        }
        D_8032787C = var_a0_8;
        var_v0_4 = var_a0_8;
        if (var_v0_4 <= 0) {
            var_v0_4 = 1;
        }
        D_8032787C = var_v0_4;
        func_800AE800();
        return;
    case 0x8:
        if (D_80327888 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 9;
        D_80327B23 = 1;
        gOpeningSequenceFinished = 1;
        D_803278D8 = 0;
        func_80079BD4();
        func_80079BB4(8);
        func_80079BF4((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            if (D_803278B0 < currentTime) {
                timeDelta = currentTime - D_803278B0;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                fadeAlpha = transitionRatio * 255.0f;
                D_803278BB = (u8) fadeAlpha;
                transitionRatio = (f32) (1.0 - (f64) transitionRatio);
                func_80079BF4((s32) (s16) (s32) (transitionRatio * (f32) (D_80125794 << 0xC)));
            }
            if (D_80327898 < currentTime) {
                D_803278B8 = 0xFF;
            }
            if (D_803278A0 < currentTime) {
                D_803278BC = 1;
                D_803278B9 = 0xFF;
            }
            if (D_803278A8 < currentTime) {
                D_803278BC = 2;
                D_803278BA = 0xFF;
            }
            func_800AEA50();
            return;
        }
    case 0xA:
        if (D_803278E0 < currentTime || (gOpeningSequenceSkipRequested != 0)) {
            gOpeningSequencePhase = 0xB;
            D_8032794C = func_800B9C0C(D_80132A34);
            D_80327930 = (func_801120A0() * 1000000ULL / D_80145DA0);
            D_80327928 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x895440ULL;
            D_80327958 = (func_801120A0() * 1000000ULL / D_80145DA0);
            D_80327960 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            D_80327968 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
            D_80327938 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            temp_ret_80 = func_801120A0();
            D_80327970 = 0;
            D_80327971 = 0;
            D_80327972 = 0;
            D_80327948 = 0;
            temp_ret_80 = temp_ret_80 * 1000000ULL / D_80145DA0;
            D_80327940 = temp_ret_80 + 0x5B8D80ULL;
            return;
        }
        if (D_80327918 < currentTime) {
            timeDelta = currentTime - D_80327918;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 3000000.0f;
            fadeAlpha = transitionRatio * 255.0f;
            D_80327923 = (u8) fadeAlpha;
        }
        if (D_80327900 < currentTime) {
            D_80327920 = 0xFF;
        }
        if (D_80327908 < currentTime) {
            if (D_803278F0 == 0) {
                D_803278F4 = func_800B9C0C(D_801329C8);
                D_803278E8 = currentTime;
                D_803278F0 = 1;
            }
            D_80327921 = 0xFF;
        }
        if (D_80327910 < currentTime) {
            if (D_803278F0 == 1) {
                D_803278F4 = func_800B9C0C(D_80132A04);
                D_803278E8 = currentTime;
                D_803278F0 = 2;
            }
            D_80327922 = 0xFF;
        }
        timeDelta = currentTime - D_803278E8;
        D_80327B28 = timeDelta;
        deltaAsFloat = (f32) timeDelta;
        var_a0_9 = D_803278F4;
        temp_f2_14 = (s32) (deltaAsFloat / 66666.0f);
        D_803278F8 = temp_f2_14;
        if (temp_f2_14 < var_a0_9) {
            var_a0_9 = temp_f2_14;
        }
        D_803278F8 = var_a0_9;
        var_v0_5 = var_a0_9;
        if (var_v0_5 <= 0) {
            var_v0_5 = 1;
        }
        D_803278F8 = var_v0_5;
        func_800AEF98();
        return;
    case 0xB:
        if (D_80327928 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 0xC;
        D_80327980 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xE4E1C0ULL;
        D_80327998 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_803279A0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        D_803279C0 = (func_801120A0() * 1000000ULL / D_80145DA0);
        D_803279A8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_803279C8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_803279B0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
        D_803279D0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        D_803279B8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_80327988 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x014FB180ULL;
        temp_ret_102 = func_801120A0();
        D_803279D8 = 0;
        D_803279DC = 0;
        D_803279DB = 0;
        D_803279DA = 0;
        D_803279D9 = 0;
        D_803279E8 = 0;
        temp_ret_102 = temp_ret_102 * 1000000ULL / D_80145DA0;
        D_80327990 = temp_ret_102 + 0x1E8480ULL;
        D_803279E9 = 1;
        func_80079BD4();
        func_80079BB4(0xF);
        func_80079BF4((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            if (D_80327940 < currentTime) {
                timeDelta = currentTime - D_80327940;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                D_80327978 = (s32) (transitionRatio * 255.0f);
            }
            if (D_80327938 < currentTime) {
                D_80327974 = 0;
            } else {
                timeDelta = D_80327938 - currentTime;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                D_80327974 = (s32) (transitionRatio * 255.0f);
            }
            if (D_80327958 < currentTime) {
                D_80327970 = 0xFF;
            }
            if (D_80327960 < currentTime) {
                if (D_80327948 == 0) {
                    D_8032794C = func_800B9C0C(D_80132A78);
                    D_80327930 = currentTime;
                    D_80327948 = 1;
                }
                D_80327971 = 0xFF;
            }
            if (D_80327968 < currentTime) {
                if (D_80327948 == 1) {
                    D_8032794C = func_800B9C0C(D_80132AA8);
                    D_80327930 = currentTime;
                    D_80327948 = 2;
                }
                D_80327972 = 0xFF;
            }
            timeDelta = currentTime - D_80327930;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_10 = D_8032794C;
            temp_f2_15 = (s32) (deltaAsFloat / 66666.0f);
            D_80327950 = temp_f2_15;
            if (temp_f2_15 < var_a0_10) {
                var_a0_10 = temp_f2_15;
            }
            D_80327950 = var_a0_10;
            var_v0_6 = var_a0_10;
            if (var_v0_6 <= 0) {
                var_v0_6 = 1;
            }
            D_80327950 = var_v0_6;
            func_800AF534();
            return;
        }
    case 0xC:
        if (D_80327980 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = -1;
        D_80327708 = 0;
        D_803276E1 = 0xFF;
        D_803276F0 = 0;
        D_803276F8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x6ACFC0ULL;
        D_803276E8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        D_80327700 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x4C4B40ULL;
        return;
        } else {
            if (D_80327990 < currentTime) {
                D_803279E4 = 0;
            } else {
                timeDelta = D_80327990 - currentTime;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 2000000.0f;
                D_803279E4 = (s32) (transitionRatio * 255.0f);
            }
            if (D_80327998 < currentTime) {
                D_803279D8 = 0;
            } else {
                timeDelta = D_80327998 - currentTime;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                fadeAlpha = transitionRatio * 255.0f;
                D_803279D8 = (u8) fadeAlpha;
            }
            if ((D_803279D9 != 0) && (D_803279E9 != 0)) {
                D_803279E8 = 1;
                func_800B9C34(0xB, 0x7000);
            }
            if (D_803279A0 < currentTime || currentTime < D_803279C0) {
                D_803279D9 = 0;
            } else {
                timeDelta = currentTime - D_803279C0;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 6000000.0f;
                if ((f64) transitionRatio < 0.5) {
                    D_803279D9 = (u8) (transitionRatio * 255.0f);
                } else {
                    D_803279D9 = (u8) ((1.0f - transitionRatio) * 255.0f);
                }
            }
            if (D_803279A8 < currentTime || currentTime < D_803279C8) {
                D_803279DA = 0;
            } else {
                timeDelta = currentTime - D_803279C8;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 6000000.0f;
                if ((f64) transitionRatio < 0.5) {
                    D_803279DA = (u8) (transitionRatio * 255.0f);
                } else {
                    D_803279DA = (u8) ((1.0f - transitionRatio) * 255.0f);
                }
            }
            if (D_803279B0 < currentTime || currentTime < D_803279D0) {
                D_803279DB = 0;
            } else {
                timeDelta = currentTime - D_803279D0;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 6000000.0f;
                if ((f64) transitionRatio < 0.5) {
                    D_803279DB = (u8) (transitionRatio * 255.0f);
                } else {
                    D_803279DB = (u8) ((1.0f - transitionRatio) * 255.0f);
                }
            }
            if (D_80327988 < currentTime) {
                timeDelta = currentTime - D_80327988;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / -7000000.0f;
                D_803279E0 = (s32) (transitionRatio * 255.0f);
            }
            func_800AFB08();
            return;
        }
    case 0xFF:
        if (D_803276E8 < currentTime) {
            D_803276E1 = 0xFF;
        } else {
            timeDelta = D_803276E8 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            transitionRatio = 1.0f - transitionRatio;
            fadeAlpha = transitionRatio * 255.0f;
            D_803276E1 = (u8) fadeAlpha;
        }
        if (D_80327700 < currentTime) {
            timeDelta = currentTime - D_80327700;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            D_80327708 = (s32) (transitionRatio * 255.0f);
        }
        if (D_803276F8 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 0xD;
        D_803279F0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_80327A00 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        D_803279F8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        D_80327A18 = (func_801120A0() * 1000000ULL / D_80145DA0);
        D_80327A20 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        temp_ret_120 = func_801120A0();
        D_80327A08 = 0;
        D_80327A0C = 0;
        temp_ret_120 = temp_ret_120 * 1000000ULL / D_80145DA0;
        D_80327A28 = temp_ret_120 + 0x3D0900ULL;
        return;
        } else {
            func_8010698C(&gFrontendDisplayList);
            func_8010555C(0xC8, 0xC8, 0xC8, D_803276E1);
            func_8010552C(0, 0x46);
            func_80105A50(&gFrontendDisplayList, D_800731CC, 0, 0x140);

            func_800F4DFC(&gFrontendDisplayList, 0, 0, 0x140, 0xF0, 0, 0, 0, D_80327708);
            return;
        }
    case 0xD:
        if (currentTime >= D_80327A00) {
            D_80327764 = 0;
        } else {
            timeDelta = D_80327A00 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            D_80327A10 = (s32) (transitionRatio * 255.0f);
        }
        if (D_803279F0 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 0xE;
        D_80327B24 = 1;
        gOpeningSequenceFinished = 1;
        D_80327A50 = 0;
        D_80327A38 = 6000000ULL;
        return;
        } else {
            if (D_803279F8 < currentTime) {
                timeDelta = currentTime - D_803279F8;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 3000000.0f;
                D_80327A0C = (s32) (transitionRatio * 255.0f);
                transitionRatio = (f32) (1.0 - (f64) transitionRatio);
                func_80079BF4((s32) (s16) (s32) (transitionRatio * (f32) (D_80125794 << 0xC)));
            }
            if (D_80327A20 < currentTime) {
                D_80327A08 = 1;
            }
            if (D_80327A28 < currentTime) {
                D_80327A08 = 2;
            }
            func_800B0210();
            return;
        }
    case 0xF:
        if (D_80327A58 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 0x10;
        temp_ret_122 = func_801120A0();
        D_80327AA1 = 0;
        temp_ret_122 = temp_ret_122 * 1000000ULL / D_80145DA0;
        D_80327A98 = temp_ret_122 + 0x2DC6C0ULL;
        D_80327AA0 = 0xFF;
        return;
        } else {
            if (D_80327A78 < currentTime) {
                D_80327A90 = 0xFF;
            }
            if (D_80327A80 < currentTime) {
                D_80327A68 = 1;
                D_80327A91 = 0xFF;
            }
            if (D_80327A88 < currentTime) {
                D_80327A68 = 2;
                D_80327A92 = 0xFF;
            }
            timeDelta = currentTime - D_80327A60;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            var_a0_11 = D_80327A6C;
            temp_f2_18 = (s32) (deltaAsFloat / 66666.0f);
            D_80327A70 = temp_f2_18;
            if (temp_f2_18 < var_a0_11) {
                var_a0_11 = temp_f2_18;
            }
            D_80327A70 = var_a0_11;
            var_v0_7 = var_a0_11;
            if (var_v0_7 <= 0) {
                var_v0_7 = 1;
            }
            D_80327A70 = var_v0_7;
            func_800B0440();
            return;
        }
    case 0x10:
        if (D_80327A98 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequencePhase = 0x11;
        D_80327AB0 = 0;
        D_80327AA8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xA7D8C0ULL;
        D_80327AB8 = (func_801120A0() * 1000000ULL / D_80145DA0);
        D_80327AC0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_80327AD0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x3D0900ULL;
        temp_ret_132 = func_801120A0();
        D_80327ADA = 0;
        D_80327AD9 = 0;
        D_80327AD8 = 0;
        temp_ret_132 = temp_ret_132 * 1000000ULL / D_80145DA0;
        D_80327AC8 = temp_ret_132 + 0x5B8D80ULL;
        return;
        } else {
            if (currentTime & 0x1111ULL) {
                D_80327AA0 = 0;
                D_80327AA1 = 0xFF;
            } else {
                D_80327AA0 = 0xFF;
                D_80327AA1 = 0;
            }
            func_800B098C();
            return;
        }
    case 0x11:
        if (D_80327AA8 < currentTime || gOpeningSequenceSkipRequested != 0) {
        gOpeningSequenceFinished = 1;
        gOpeningSequencePhase = 0x12;
        D_80327AE0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
        D_80327AF0 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        D_80327AE8 = (func_801120A0() * 1000000ULL / D_80145DA0) + 0x989680ULL;
        D_80327B10 = (func_801120A0() * 1000000ULL / D_80145DA0);
        temp_ret_142 = func_801120A0();
        D_80327AF8 = 0;
        D_80327AFC = 0;
        temp_ret_142 = temp_ret_142 * 1000000ULL / D_80145DA0;
        D_80327B18 = temp_ret_142 + 0x5B8D80ULL;
        return;
        } else {
            if (D_80327AC0 < currentTime) {
                D_80327AB0 = 1;
                D_80327AD9 = 0xFF;
            }
            if (D_80327AC8 < currentTime) {
                D_80327AB0 = 2;
                D_80327ADA = 0xFF;
            }
            if (currentTime >= D_80327AC0 && D_80327AD0 >= currentTime) {
                timeDelta = D_80327AD0 - currentTime;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 1000000.0f;
                transitionRatio = 1.0f - transitionRatio;
                fadeAlpha = transitionRatio * 255.0f;
                D_80327AD9 = (u8) fadeAlpha;
            }
            func_800B0D1C();
            return;
        }
    case 0x12:
        if (gOpeningSequenceSkipRequested != 0) {
            D_80327AF8 += 1;
        }
        if (currentTime >= D_80327AF0) {
            D_80327B00 = 0;
        } else {
            timeDelta = D_80327AF0 - currentTime;
            D_80327B28 = timeDelta;
            deltaAsFloat = (f32) timeDelta;
            transitionRatio = deltaAsFloat / 2000000.0f;
            D_80327B00 = (s32) (transitionRatio * 255.0f);
        }
        if (D_80327AE0 < currentTime || D_80327AF8 >= 2) {
            gOpeningSequenceFinished = 1;
            return;
        } else {
            if (D_80327AE8 < currentTime) {
                timeDelta = currentTime - D_80327AE8;
                D_80327B28 = timeDelta;
                deltaAsFloat = (f32) timeDelta;
                transitionRatio = deltaAsFloat / 2000000.0f;
                D_80327AFC = (s32) (transitionRatio * 255.0f);
            }
            if (D_80327B10 < currentTime) {
                D_80327B04 = 0xFF;
            }
            if (D_80327B18 < currentTime) {
                D_80327AF8 = 1;
                D_80327B08 = 0xFF;
            }
            func_800B1264();
            return;
        }
    }
}
