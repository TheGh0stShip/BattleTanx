#include "types.h"

typedef struct PairUnitState {
    u8 pad00[0x98];
    s32 value98;
} PairUnitState;

typedef struct PairUnit {
    u8 pad000[0x1];
    u8 active;
    u8 pad002[0x14 - 0x2];
    u16 flags;
    u8 pad016[0x24 - 0x16];
    f32 posX;
    u8 pad028[0x4];
    f32 posZ;
    u8 pad030[0x98 - 0x30];
    s32 value98;
    s32 mode;
    f32 *anchor;
    u8 padA4[0xB0 - 0xA4];
    PairUnitState *state;
    u8 padB4[0x34A - 0xB4];
    u8 value34A;
} PairUnit;

typedef struct UnitPair {
    u8 firstId;
    u8 secondId;
    u8 enabled;
    u8 value03;
    u8 checked;
    u8 linked;
    u8 inRange;
    u8 value07;
    f32 distance;
} UnitPair;

typedef struct PairPoint {
    f32 z;
    f32 x;
} PairPoint;

typedef struct PairSearchBuffer {
    u8 data[0x200];
} PairSearchBuffer;

extern PairUnit *get_unit(s32 id) __asm__("func_800A03B8");
extern f32 ai_horizontal_distance(void *a, void *b) __asm__("func_800E0C8C");
extern f32 get_scaled_difficulty(void) __asm__("func_800DDC68");
extern s32 entity_state_is_two(PairUnit *unit) __asm__("func_800E3460");
extern void resolve_unit_pair(s32 firstId, s32 secondId, f32 amount) __asm__("func_800E1F14");
extern void initialize_bitstream_header(PairSearchBuffer *buffer) __asm__("func_800DDCA4");
extern s32 func_800DE664(PairSearchBuffer *buffer, PairPoint *from, PairPoint *to, s32 arg3, s32 arg4);

void update_unit_pair_link(UnitPair *pair) __asm__("func_800E56B0");

void update_unit_pair_link(UnitPair *pair) {
    PairUnit *a;
    PairUnit *b;
    u8 wasLinked;
    PairPoint pointA;
    PairPoint pointB;
    PairPoint target;
    PairSearchBuffer buffer;
    f32 distance;
    s32 inRange;
    f32 *anchorA;
    f32 *anchorB;
    s32 noAnchorA;
    s32 noAnchorB;
    f32 anchorDistance;
    f32 toAnchorB;
    f32 toAnchorA;

    a = get_unit(pair->firstId);
    b = get_unit(pair->secondId);
    wasLinked = pair->linked;
    pair->checked = 0;
    pair->linked = 0;
    pair->inRange = 0;
    pair->value07 = 0;
    pair->distance = 0.0f;
    pair->value03 = 0;
    if (a->active == 0 || b->active == 0) {
        return;
    }
    pointA.x = a->posX;
    pointA.z = a->posZ;
    pointB.x = b->posX;
    pointB.z = b->posZ;
    distance = ai_horizontal_distance(&pointA, &pointB);
    pair->distance = distance;
    inRange = distance < get_scaled_difficulty();
    pair->checked = 1;
    pair->inRange = inRange;
    if (pair->enabled && inRange) {
        anchorA = a->anchor;
        anchorB = b->anchor;
        noAnchorA = anchorA == 0;
        noAnchorB = anchorB == 0;
        if (noAnchorA | noAnchorB) {
            if (distance <= 400.0f && entity_state_is_two(a) && entity_state_is_two(b) && !(a->flags & 4)
                && !(b->flags & 4)) {
                if (noAnchorA && anchorB != 0) {
                    resolve_unit_pair(pair->firstId, pair->secondId, distance);
                } else if (anchorA != 0 && noAnchorB) {
                    resolve_unit_pair(pair->secondId, pair->firstId, distance);
                }
            }
            return;
        }
        anchorDistance = ai_horizontal_distance(anchorA, anchorB);
        toAnchorB = ai_horizontal_distance(&pointA, anchorB);
        toAnchorA = ai_horizontal_distance(&pointB, anchorA);
        if (entity_state_is_two(a) && entity_state_is_two(b) && !(a->flags & 4) && !(b->flags & 4)) {
            if (anchorDistance <= 400.0f || toAnchorB <= 400.0f || toAnchorA <= 400.0f
                || (wasLinked && distance <= 400.0f)) {
                pair->linked = 1;
                if (a->value34A != 0 && b->value34A != 0) {
                    if (b->mode == 8 && b->state->value98 != 0) {
                        resolve_unit_pair(pair->firstId, pair->secondId, distance);
                    } else if (a->mode == 8 && a->state->value98 != 0) {
                        resolve_unit_pair(pair->secondId, pair->firstId, distance);
                    } else if (b->value98 != 0) {
                        resolve_unit_pair(pair->firstId, pair->secondId, distance);
                    } else if (a->value98 != 0) {
                        resolve_unit_pair(pair->secondId, pair->firstId, distance);
                    } else if (toAnchorB < toAnchorA) {
                        resolve_unit_pair(pair->secondId, pair->firstId, distance);
                    } else {
                        resolve_unit_pair(pair->firstId, pair->secondId, distance);
                    }
                }
            }
        }
    } else if (inRange) {
        target.x = b->posX;
        target.z = b->posZ;
        initialize_bitstream_header(&buffer);
        if ((u16)func_800DE664(&buffer, &pointA, &target, 1, 0)) {
            pair->linked = 1;
        }
    }
}
