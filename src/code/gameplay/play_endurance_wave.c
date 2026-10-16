#include "types.h"

/* RODATA_VRAM 0x80071138 */

/* LDSYM func_8007BD24=0x8007BD24 */
/* LDSYM func_80079064=0x80079064 */
/* LDSYM func_800A6688=0x800A6688 */
/* LDSYM D_8012578C=0x8012578C */
/* LDSYM D_801B4AD4=0x801B4AD4 */
/* LDSYM D_801B4AD8=0x801B4AD8 */
/* LDSYM D_801B4AE4=0x801B4AE4 */

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
    s32 header[6];
    AiSkillProfile skills[3][4];
    u8 pad1CC[0x18];
    s32 value1E4;
    u8 pad1E8[0x20];
    s32 round;
    s16 bonus;
    u8 pad20E[9];
    u8 group;
    u8 pad218[8];
} CampaignWave;

typedef struct CampaignParams {
    s32 value00;
    s32 result;
    s16 value08;
} CampaignParams;

typedef struct EntityRecord {
    u8 pad00[0x34];
    s32 value34;
} EntityRecord;

extern void func_8007BD24(CampaignWave *wave, CampaignParams *params);
extern void func_80079064(void);
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 gGameMode __asm__("D_8012578C");
extern s32 D_801B4AD4;
extern s32 D_801B4AD8;
extern s32 D_801B4AE4;

void play_endurance_wave(CampaignWave *wave, CampaignParams *params) __asm__("func_8007B9E4");

void play_endurance_wave(CampaignWave *wave, CampaignParams *params) {
    s32 total;
    f32 saved[4][4];
    f32 base;
    s32 group;
    s32 i;

    if (wave->kind == 7) {
        base = wave->round;
        group = wave->group;
        D_801B4AE4 = 0;
        for (i = 1; i < 4; i++) {
            saved[0][i] = wave->skills[group][i].value1C[0];
            saved[1][i] = wave->skills[group][i].value1C[1];
            saved[2][i] = wave->skills[group][i].value08;
            saved[3][i] = wave->skills[group][i].value0C;
        }
        total = wave->bonus;
        gGameMode = 10;
        D_801B4AD4 = 1;
        D_801B4AD8 = total;
        func_8007BD24(wave, params);
        func_80079064();
        D_801B4AE4 += get_entity_record(0)->value34;
        total += get_entity_record(0)->value34;
        while (params->result != 0) {
            wave->round += 3;
            for (i = 1; i < 4; i++) {
                wave->skills[group][i].value1C[0] = saved[0][i] + (f64)(wave->round - base) / base;
                wave->skills[group][i].value1C[1] = saved[1][i] / ((f64)(wave->round - base) / base + 1.0);
                wave->skills[group][i].value08 = saved[2][i] / ((f64)(wave->round - base) * 0.4 / base + 1.0);
                wave->skills[group][i].value0C = saved[3][i] / ((f64)(wave->round - base) * 0.4 / base + 1.0);
            }
            wave->value1E4 = params->value00;
            func_80079064();
            gGameMode = 10;
            D_801B4AD4 = 1;
            func_8007BD24(wave, params);
            func_80079064();
            total += get_entity_record(0)->value34;
            D_801B4AE4 += get_entity_record(0)->value34;
        }
        params->value08 = total;
    } else {
        func_8007BD24(wave, params);
    }
}
