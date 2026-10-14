#include "types.h"

typedef struct SnapshotBlock {
    u32 words[16];
} SnapshotBlock;

typedef struct SnapshotEntity {
    u8 pad00[0x100];
    SnapshotBlock block;
} SnapshotEntity;

typedef struct EntitySnapshot {
    SnapshotBlock block;
    s32 value40;
} EntitySnapshot;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern SnapshotEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800A424C(SnapshotEntity *entity);
extern void draw_bucket_items(s32 bucket, u8 *arg1, u16 *arg2) __asm__("func_80080C60");
extern EntitySnapshot D_801C9058[];
extern u16 D_801C9050[];

void snapshot_entity_blocks(void) __asm__("func_80081934");

void snapshot_entity_blocks(void) {
    s32 count = get_difficulty_level();
    u16 i;

    for (i = 0; i < count; i++) {
        SnapshotEntity *entity = get_entity_record(i);
        func_800A424C(entity);
        D_801C9058[i].block = entity->block;
        D_801C9058[i].value40 = 0;
    }
    draw_bucket_items(0, (u8 *)D_801C9058, D_801C9050);
}
