#include "types.h"

typedef struct TeamEntity {
    u8 pad000[0x1AE];
    u8 team;
    u8 active;
    u8 pad1B0[0x198];
} TeamEntity;

extern TeamEntity D_802DE620[];
extern u8 gActiveEntityTotal __asm__("D_802DF340");
extern u8 gTeamActiveCounts[] __asm__("D_802DF344");
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");

void recount_team_active_entities(void) __asm__("func_800A66C8");

void recount_team_active_entities(void)
{
    u16 i;
    s32 count;
    TeamEntity *entity;

    for (i = 0; i < 4; i++) {
        gTeamActiveCounts[i] = 0;
    }
    gActiveEntityTotal = 0;
    count = get_entity_capacity();
    for (i = 0; i < count; i++) {
        entity = &D_802DE620[i];
        gActiveEntityTotal += entity->active;
        gTeamActiveCounts[entity->team] += entity->active;
    }
}
