#include "types.h"

typedef struct EntityProgress {
    u8 pad000[0x210];
    s32 progress;
} EntityProgress;

extern s32 progress_events_enabled(void) __asm__("func_8007C700");
extern void handle_entity_progress_threshold(EntityProgress *entity, s32 threshold)
    __asm__("func_800A5DD8");

void add_entity_progress(EntityProgress *entity, s32 amount) __asm__("func_800A59E8");

void add_entity_progress(EntityProgress *entity, s32 amount)
{
    s32 progress;
    s32 previousThreshold;
    s32 newThreshold;

    progress = entity->progress + amount;
    newThreshold = progress / 50000;
    previousThreshold = entity->progress / 50000;
    if (previousThreshold < newThreshold && progress_events_enabled() != 0) {
        handle_entity_progress_threshold(entity, newThreshold * 50000);
    }
    entity->progress = progress;
}
