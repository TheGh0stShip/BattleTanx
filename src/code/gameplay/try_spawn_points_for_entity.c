#include "types.h"

typedef struct SpawnPoint {
    u8 pad000[0x280];
    s32 value00;
    s32 value04;
    u16 value08;
    u8 pad0A[0x2];
} SpawnPoint;

typedef struct SpawnSession SpawnSession;

typedef struct SpawnEntity {
    u8 pad00[0x4];
    u8 slot;
} SpawnEntity;

extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s32 try_spawn_at_point(SpawnEntity *entity, s32 a, s32 b, u16 c) __asm__("func_8009FEE0");

s32 try_spawn_points_for_entity(SpawnEntity *entity) __asm__("func_800A0134");

s32 try_spawn_points_for_entity(SpawnEntity *entity)
{
    SpawnSession *session = get_spawn_session();
    s32 i;
    s32 j;
    s32 offset;
    SpawnPoint *point;

    for (i = 0; i < get_entity_capacity(); i++) {
        j = 0;
        offset = ((entity->slot + i) % get_entity_capacity()) * 0x3C;
        do {
            point = (SpawnPoint *) ((u8 *) session + offset);
            if (try_spawn_at_point(entity, point->value00, point->value04, point->value08) >= 0) {
                return 1;
            }
            j++;
            offset += 0xC;
        } while (j < 5);
    }
    return -1;
}
