#include "types.h"

typedef struct AiSkillProfile {
    f32 aggressiveness;
    f32 intelligence;
    s32 offense;
    s32 defense;
    s32 gunResurrection;
    s16 *gunDamage;
    s16 *gunFireRate;
    u8 aiSpeedFactor;
    u8 aiFireRate;
    u8 railFireRate;
    u8 offRailFireRate;
    u8 railSpeedFactor;
    u8 pad21[3];
} AiSkillProfile;

typedef struct TeamInfo {
    u8 pad00[0x18];
    AiSkillProfile profile;
} TeamInfo;

typedef struct TeamTuning {
    u8 pad000[0xC];
    s32 id;
    u8 pad010[0x180];
    f32 aggressiveness;
    f32 intelligence;
    u8 pad198[8];
    f32 railSpeedFactor;
    u8 pad1A4[0x16C];
    f32 offense;
    f32 defense;
    f32 gunResurrection;
    f32 aiSpeedFactor;
    f32 aiFireRate;
    f32 railFireRate;
    f32 offRailFireRate;
    f32 railSpeedTuning;
    f32 aggressivenessTuning;
    f32 intelligenceTuning;
    s16 gunDamage[4];
    s16 gunFireRate[4];
} TeamTuning;

typedef struct CampaignWave {
    s32 kind;
    u32 level;
    u8 pad08[0x14];
    AiSkillProfile skills[3][4];
    u8 pad1CC[4];
    s32 teamCount;
    u8 pad1D4[0x40];
    u8 color[3];
    u8 group;
    u8 pad218[8];
} CampaignWave;

extern TeamTuning *get_entity_record(u16 index) __asm__("func_800A6688");
extern TeamInfo *get_entity_info(s32 id) __asm__("func_800A68C0");
extern void func_8007D2A0(u32 level);
extern CampaignWave *gCurrentGameState __asm__("D_801B4ABC");
extern CampaignWave gOpponentWaves[17] __asm__("D_80142DE8");
extern s32 D_801B4AD0;
extern s32 D_80134E5C;

#define APPLY(field, value)                    \
    if (info->field != 0) {                    \
        info->field = value;                   \
    } else {                                   \
        profile->field = value;                \
    }

void apply_team_tuning(void) __asm__("func_8007CCD0");

void apply_team_tuning(void) {
    CampaignWave *state = gCurrentGameState;
    u8 group = state->group;
    TeamTuning *team;
    AiSkillProfile *profile;
    AiSkillProfile *info;
    u16 i;
    u16 k;

    if (D_80134E5C == 0) {
        CampaignWave *wave = &gOpponentWaves[D_801B4AD0];

        wave->color[0] = state->color[0];
        wave->color[1] = state->color[1];
        wave->color[2] = state->color[2];
    }
    for (i = 0; i < state->teamCount; i++) {
        team = get_entity_record(i);
        profile = &state->skills[group][i];
        info = &get_entity_info(team->id)->profile;
        team->aggressiveness = team->aggressivenessTuning / 100.0f;
        if (info->aggressiveness != 0.0f) {
            info->aggressiveness = team->aggressivenessTuning / 100.0f;
        } else {
            profile->aggressiveness = team->aggressivenessTuning / 100.0f;
        }
        team->intelligence = team->intelligenceTuning / 100.0f;
        if (info->intelligence != 0.0f) {
            info->intelligence = team->intelligenceTuning / 100.0f;
        } else {
            profile->intelligence = team->intelligenceTuning / 100.0f;
        }
        APPLY(offense, team->offense);
        APPLY(defense, team->defense);
        APPLY(aiSpeedFactor, team->aiSpeedFactor);
        APPLY(aiFireRate, team->aiFireRate);
        APPLY(railFireRate, team->railFireRate);
        APPLY(offRailFireRate, team->offRailFireRate);
        team->railSpeedFactor = team->railSpeedTuning;
        APPLY(railSpeedFactor, team->railSpeedTuning);
        APPLY(gunResurrection, team->gunResurrection);
        for (k = 0; k < 4; k++) {
            APPLY(gunDamage[k], team->gunDamage[k]);
            APPLY(gunFireRate[k], team->gunFireRate[k]);
        }
    }
    func_8007D2A0(gCurrentGameState->level);
}
