#include "types.h"

typedef struct NearestBuffer {
    u8 data[0x200];
} NearestBuffer;

typedef struct PlanarPoint {
    f32 value0;
    f32 value4;
} PlanarPoint;

typedef struct NearestItem {
    u8 pad00[0x8];
    s32 value08;
    PlanarPoint position;
    u8 pad14[0x4];
    s32 value18;
    u8 pad1C[0x4];
    u8 value20;
} NearestItem;

typedef struct NearestQuery {
    u8 pad00[0x24];
    f32 value24;
    u8 pad28[0x4];
    f32 value2C;
} NearestQuery;

typedef struct NearestNode {
    u8 pad00[0xA];
    s16 next;
    u8 pad0C[0x4];
    NearestItem *item;
    u8 pad14[0x14];
} NearestNode;

extern f32 D_800744D0;
extern s32 gNearestNodeHead __asm__("D_803B8240");
extern NearestNode gNearestNodes[] __asm__("D_803B8240");

extern void initialize_bitstream_header(NearestBuffer *header) __asm__("func_800DDCA4");
extern u16 func_800DE3EC(NearestBuffer *header, PlanarPoint *position);
extern f32 func_800E0C8C(PlanarPoint *a, PlanarPoint *b);
extern u8 get_mapped_runtime_status(u16 index) __asm__("func_800E19DC");
extern u8 byte_mask_intersects(u32 value, u32 mask) __asm__("func_800E1A08");

NearestItem *find_nearest_available_item(NearestQuery *query) __asm__("func_800E1A84");

NearestItem *find_nearest_available_item(NearestQuery *query)
{
    NearestBuffer buffer;
    PlanarPoint point;
    f32 best;
    f32 distance;
    NearestItem *found;
    NearestItem *item;
    s16 i;
    u16 id;

    best = D_800744D0;
    initialize_bitstream_header(&buffer);
    found = 0;
    point.value4 = query->value24;
    point.value0 = query->value2C;
    for (i = gNearestNodeHead; i != -1; i = gNearestNodes[i].next) {
        item = gNearestNodes[i].item;
        if (item != 0 && item->value08 == 3 && item->value18 == 0 && item->value20 == 0) {
            distance = func_800E0C8C(&point, &item->position);
            if (best <= distance) {
                continue;
            }
            id = func_800DE3EC(&buffer, &item->position);
            if (id != 0 && !byte_mask_intersects(get_mapped_runtime_status(id), 3)) {
                found = item;
                best = distance;
            }
        }
    }
    return found;
}
