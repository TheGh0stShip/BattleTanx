#include "types.h"

typedef struct RenderItem {
    s32 displayList;
    s32 material;
    s32 state;
    struct RenderItem *next;
} RenderItem;

typedef struct RenderBatch {
    u32 key;
    RenderItem *playerItems[4];
    struct RenderBatch *next;
} RenderBatch;

typedef struct PlayerViewCache {
    u8 matrices[4][0x44];
    u16 matrixParams[4];
} PlayerViewCache;

extern s32 get_player_count(void) __asm__("func_8007AAA0");
extern void push_cached_matrix_params(void *matrix, u16 params) __asm__("func_8007E8EC");
extern void set_render_material(s32 material, s32 mode) __asm__("func_8007EB64");
extern void submit_display_list(s32 displayList) __asm__("func_8007EEF8");
extern void set_render_state(s32 enabled, s32 state) __asm__("func_8007EF64");
extern s32 get_entity_render_key(void *entity) __asm__("func_800A42A4");
extern void *get_player_entity(u16 playerIndex) __asm__("func_800A6688");

extern RenderBatch *gRenderBatchBuckets[32] __asm__("D_801C0A40");
extern PlayerViewCache gPlayerViewCache __asm__("D_801C8F40");

void draw_cached_render_batches(void) __asm__("func_80081788");

void draw_cached_render_batches(void)
{
    s32 lastPlayer = -1;
    s32 lastMaterial = 0;
    s32 playerCount = get_player_count();
    s32 bucketIndex;
    RenderBatch *batch;
    RenderItem *item;
    s32 playerIndex;
    s32 lastState;

    for (bucketIndex = 0; bucketIndex < 32; bucketIndex++) {
        for (batch = gRenderBatchBuckets[bucketIndex]; batch != 0; batch = batch->next) {
            lastState = 0;
            submit_display_list(batch->key);
            for (playerIndex = 0; playerIndex < playerCount; playerIndex++) {
                for (item = batch->playerItems[playerIndex]; item != 0; item = item->next) {
                    if (playerIndex != lastPlayer) {
                        submit_display_list(get_entity_render_key(get_player_entity(playerIndex)));
                        lastPlayer = playerIndex;
                        push_cached_matrix_params(
                            gPlayerViewCache.matrices[playerIndex],
                            gPlayerViewCache.matrixParams[playerIndex]);
                    }
                    if (item->material != lastMaterial) {
                        set_render_material(item->material, 2);
                        lastMaterial = item->material;
                    }
                    if (item->state != lastState && item->state != 0) {
                        set_render_state(1, item->state);
                        lastState = item->state;
                    }
                    submit_display_list(item->displayList);
                }
            }
        }
    }
}
