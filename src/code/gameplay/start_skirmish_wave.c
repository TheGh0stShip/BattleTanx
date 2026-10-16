#include "types.h"

typedef struct AiSkillProfile {
    f32 value00;
    f32 value04;
    s32 value08;
    s32 value0C;
    s32 value10;
    void *rangeA;
    void *rangeB;
    u8 value1C[4];
    u8 value20;
    u8 pad21[3];
} AiSkillProfile;

typedef struct CampaignWave {
    s32 kind;
    s32 level;
    s32 value08;
    s32 colors[4];
    AiSkillProfile skills[3][4];
    s32 value1CC;
    s32 value1D0;
    s32 value1D4;
    s32 value1D8[3];
    s32 value1E4;
    s32 value1E8;
    s32 value1EC;
    s32 value1F0;
    s32 value1F4;
    u8 pad1F8[0xC];
    s32 value204;
    s32 round;
    s16 bonus;
    u8 pad20E[6];
    u8 value214;
    u8 value215;
    u8 value216;
    u8 group;
    u8 pad218[8];
} CampaignWave;

typedef struct CampaignParams {
    s32 value00;
    s32 result;
    s16 value08;
    u8 pad0A[0x18];
} CampaignParams;

typedef struct SessionSlot {
    u8 pad00[8];
    u8 level;
    u8 pad09[3];
    s32 value0C;
    u8 pad10[4];
    s16 value14;
} SessionSlot;

typedef struct FrontendSession {
    u8 pad00[0xC];
    CampaignWave *wave;
} FrontendSession;

extern s32 D_8012578C;
extern s32 D_801B4AD4;
extern s32 D_801B4AB8;
extern u8 D_80125798;
extern s8 D_801B4AE0;
extern s32 D_80134020[4];
extern s32 D_80134E58;
extern s32 D_80134E5C;
extern u8 D_80134E68;
extern SessionSlot *D_80134E78;
extern s32 D_80135674;
extern AiSkillProfile D_80145208;
extern AiSkillProfile D_8014522C;
extern AiSkillProfile D_80145250;
extern AiSkillProfile D_80145274;
extern FrontendSession D_801B4AB0;
extern s32 D_803283C0;
extern s32 D_803283C4;
extern s32 D_80328400[4];
extern void func_800D68D0(s32 arg0);
extern void run_campaign_waves(s32 index, s32 id, s32 offset, s16 bonus) __asm__("func_8007B280");
extern void play_endurance_wave(CampaignWave *wave, CampaignParams *params) __asm__("func_8007B9E4");

s32 start_skirmish_wave(u16 mode) __asm__("func_8007B590");

s32 start_skirmish_wave(u16 mode)
{
    CampaignWave wave;
    CampaignParams params;
    s32 t;
    s32 j;

    D_8012578C = 10;
    D_801B4AD4 = 1;
    if (mode != 2 && D_80134E58 == 1 && D_80134E5C == 0) {
        D_80135674 = D_80134E78->level;
        func_800D68D0(1);
        run_campaign_waves(0, D_80135674, D_80134E78->value0C, D_80134E78->value14);
        return 0;
    }
    wave.group = 1;
    for (t = 0; t < 4; t++) {
        if (D_80135674 != 0) {
            wave.skills[0][t] = D_8014522C;
            wave.skills[1][t] = D_80145250;
            wave.skills[2][t] = D_80145274;
        } else {
            for (j = 0; j < 3; j++) {
                wave.skills[j][t] = D_80145208;
            }
        }
    }
    wave.value214 = 0x14;
    wave.value215 = 0x33;
    wave.value216 = 0x33;
    D_80134E68 = 0;
    if (mode == 2) {
        wave.kind = 8;
        wave.colors[0] = 13;
        wave.colors[1] = 13;
        wave.colors[2] = 13;
        wave.colors[3] = 13;
    } else {
        wave.colors[0] = D_80134020[0];
        wave.colors[1] = D_80134020[1];
        wave.colors[2] = D_80134020[2];
        wave.colors[3] = D_80134020[3];
        switch (D_80134E5C) {
        case 3:
            wave.kind = 9;
            break;
        case 2:
            wave.kind = 0;
            break;
        case 4:
            wave.kind = 9;
            D_80134E68 = 1;
            break;
        default:
            wave.kind = 2;
            break;
        }
    }
    wave.value1E4 = 0;
    wave.value1E8 = 0;
    wave.value1EC = 0;
    wave.value1F0 = 0;
    wave.value1F4 = 3;
    wave.value1D4 = D_80328400[0];
    wave.value1CC = D_80134E58;
    wave.value1D0 = D_801B4AB8 = D_803283C4;
    wave.level = D_80135674;
    wave.value204 = D_803283C0;
    wave.value1D8[0] = D_80328400[1];
    wave.value1D8[1] = D_80328400[2];
    wave.value1D8[2] = D_80328400[3];
    if (((D_80135674 == 9) | (D_80135674 == 17) || (D_80135674 == 5) | (D_80135674 == 13)) && wave.kind != 8) {
        wave.kind = 7;
        wave.colors[0] = 12;
        wave.colors[1] = 13;
        wave.colors[2] = 13;
        wave.colors[3] = 13;
        wave.value1D0 = D_801B4AB8 = 4;
        wave.value1CC = 1;
        wave.value1D4 = 0;
        wave.value1D8[0] = 1;
        wave.value1D8[1] = 1;
        wave.value1D8[2] = 1;
        wave.round = 5;
    }
    if (D_80134E68 != 0) {
        wave.colors[0] = 0;
        wave.colors[1] = 0;
        wave.colors[2] = 0;
        wave.colors[3] = 0;
    }
    D_801B4AB0.wave = &wave;
    play_endurance_wave(&wave, &params);
    if (D_80125798 == 0) {
        D_801B4AE0 = 2;
    }
    return 0;
}
