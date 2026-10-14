#include "types.h"

typedef struct NearestItem {
    u8 pad00[0x8];
    s32 value08;
    u8 pad0C[0x4];
    u8 position[0x15];
    u8 value25;
} NearestItem;

typedef struct NearestQuery {
    u8 pad00[0x24];
    u8 position[0xC];
} NearestQuery;

typedef struct NearestNode {
    u8 pad00[0xA];
    s16 next;
    u8 pad0C[0x4];
    NearestItem *item;
    u8 pad14[0x14];
} NearestNode;

extern s32 gNearestNodeHead __asm__("D_803B8240");
extern NearestNode gNearestNodes[] __asm__("D_803B8240");

extern f32 approx_xz_distance(void *a, void *b) __asm__("func_800E0D54");

NearestItem *find_nearest_kind1a_item(NearestQuery *query) __asm__("func_800E1C00");

NearestItem *find_nearest_kind1a_item(NearestQuery *query)
{
    f32 best;
    f32 distance;
    NearestItem *found;
    NearestItem *item;
    s16 i;

    best = 16000.0f;
    found = 0;
    for (i = gNearestNodeHead; i != -1; i = gNearestNodes[i].next) {
        item = gNearestNodes[i].item;
        if (item != 0 && item->value08 == 0x1A && item->value25 == 0) {
            distance = approx_xz_distance(query->position, item->position);
            if (!(800.0f <= distance) && !(best <= distance)) {
                found = item;
                best = distance;
            }
        }
    }
    return found;
}
