#include "types.h"

typedef struct AiGroup {
    s16 entityIds[3];
    u16 entityCount;
    s16 unitIds[15];
    u16 unitCount;
} AiGroup;

typedef struct AiTeam {
    AiGroup own;
    AiGroup allies;
    u8 active;
    u8 pad51;
} AiTeam;

typedef struct TeamEntityRecord {
    s16 members[5];
    u8 pad0A[0x1AE - 0xA];
    u8 teamIndex;
} TeamEntityRecord;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern u16 get_entity_count(void) __asm__("func_800A66B0");
extern TeamEntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 func_800E66BC(u16 teamCount, AiTeam *teams);
extern AiTeam D_8033A980[4];
extern s32 D_8033AAC8[4];
extern u16 D_80135894;
extern s32 D_80135890;

static inline void ai_group_add_entity(AiGroup *group, u16 entityIndex) {
    TeamEntityRecord *record = get_entity_record(entityIndex);
    u16 i;
    s16 id;

    group->entityIds[group->entityCount] = entityIndex;
    group->entityCount++;
    for (i = 0; i < 5; i++) {
        id = record->members[i];
        get_unit(id);
        group->unitIds[group->unitCount] = id;
        group->unitCount++;
    }
}

void ai_build_team_groups(void) __asm__("func_800E4DF8");

void ai_build_team_groups(void) {
    s32 used[4];
    AiTeam *team;
    AiTeam *other;
    AiTeam *cleared;
    u16 entityCount;
    u16 slot;
    u16 init;
    u16 entity;
    u16 t;
    u16 o;
    u16 k;
    u16 n;
    u8 teamIndex;

    for (slot = 0; slot < 4; slot++) {
        D_8033AAC8[slot] = 0;
    }
    D_80135894 = 4;
    for (init = 0; init < 4; init++) {
        used[init] = 0;
        cleared = &D_8033A980[init];
        cleared->allies.entityCount = 0;
        cleared->allies.unitCount = 0;
        cleared->own.entityCount = 0;
        cleared->own.unitCount = 0;
        cleared->active = 0;
    }
    entityCount = get_entity_count();
    for (entity = 0; entity < entityCount; entity++) {
        teamIndex = get_entity_record(entity)->teamIndex;
        used[teamIndex] = 1;
        D_8033A980[teamIndex].active = 1;
        ai_group_add_entity(&D_8033A980[teamIndex].own, entity);
    }
    for (t = 0; t < D_80135894; t++) {
        team = &D_8033A980[t];
        if (team->active != 0) {
            for (o = 0; o < D_80135894; o++) {
                if (t != o) {
                    other = &D_8033A980[o];
                    if (other->active != 0) {
                        for (k = 0; k < other->own.entityCount; k++) {
                            ai_group_add_entity(&team->allies, other->own.entityIds[k]);
                        }
                    }
                }
            }
        }
    }
    for (n = 0; n < get_entity_capacity(); n++) {
        D_8033AAC8[n] = 1;
    }
    D_80135890 = func_800E66BC(D_80135894, D_8033A980);
}
