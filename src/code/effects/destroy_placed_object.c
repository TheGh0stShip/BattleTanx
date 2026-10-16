#include "types.h"
/* RODATA_VRAM 0x80071CE0 */
/* LDSYM D_802C3800=0x802C3800 */
/* LDSYM D_803B8254=0x803B8254 */
/* LDSYM func_8007AAA0=0x8007AAA0 */
/* LDSYM func_800821C0=0x800821C0 */
/* LDSYM func_80085B4C=0x80085B4C */
/* LDSYM func_8008F6F4=0x8008F6F4 */
/* LDSYM func_8009F958=0x8009F958 */
/* LDSYM func_800ED8C0=0x800ED8C0 */
/* LDSYM func_800F38F4=0x800F38F4 */
/* LDSYM func_80107170=0x80107170 */
/* LDSYM func_80107A14=0x80107A14 */

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct AreaObject {
    u8 pad00[8];
    s32 kind;
} AreaObject;

typedef void (*AreaHandler)(AreaObject *object, void *source, s32 arg2, void *message, void *response);

typedef struct AreaHandlerEntry {
    s32 value00;
    AreaHandler handler;
    s32 value08;
} AreaHandlerEntry;

typedef struct PlacedRecord {
    u8 flags;
    u8 pad01[0x4F];
    u16 angle;
    s16 group;
    u16 model;
    u8 pad56[2];
} PlacedRecord;

typedef struct ModelGroupRef {
    u8 kind;
    u8 pad01;
    u16 first;
} ModelGroupRef;

typedef struct ModelEntry {
    u8 pad00[2];
    u16 first;
    u8 pad04[8];
} ModelEntry;

typedef struct PartList {
    u8 count;
    u8 pad01;
    u16 first;
} PartList;

typedef struct PartRecord {
    u8 pad00[0xC];
} PartRecord;

typedef struct ObjectSession {
    u8 pad000[0x568];
    PlacedRecord *objects;
    ModelGroupRef *groups;
    ModelEntry *models;
    PartList *lists;
    PartRecord *parts;
} ObjectSession;

typedef struct DestroyedObject {
    u8 pad00[0xC];
    s32 x;
    s32 z;
    s32 object;
    s32 area;
    u8 debris;
    u8 flags;
    u16 heading;
} DestroyedObject;

extern void spawn_effect_kind_26(Vec3f *position, s32 variant) __asm__("func_800ED8C0");
extern void notify_objects_near_point(DestroyedObject *sender, f32 *point, f32 radius, f32 value, u8 flag)
    __asm__("func_8009F958");
extern u8 find_objects_in_area(void *box, s32 capacity, AreaObject **results, s32 *count) __asm__("func_80107A14");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern ObjectSession *get_spawn_session(void) __asm__("func_800821C0");
extern u32 random_u32(void) __asm__("func_800F38F4");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern s32 spawn_part_debris(Vec3f *position, u16 angleX, u16 angleY, u16 angleZ, u16 spinX, u16 spinY, u16 spinZ,
                             u16 heading, u16 pitchMax, u16 pitchMin, f32 speedScale, PartRecord *part,
                             s32 value3C, u8 flags) __asm__("func_8008F6F4");
extern void free_effect_area(s32 handle) __asm__("func_80107170");
extern AreaHandlerEntry D_802C3800[];
extern u8 D_803B8254[][0x28];

void destroy_placed_object(DestroyedObject *self, s32 *state) __asm__("func_8008FD6C");

void destroy_placed_object(DestroyedObject *self, s32 *state) {
    Vec3f position;
    AreaObject *found[32];
    u8 message[0x20];
    u8 response[0x10];
    f32 point[2];
    s32 count;
    ObjectSession *session;
    PlacedRecord *record;
    ModelEntry *model;
    PartList *list;
    s32 i;
    s32 j;
    u8 flags;

    position.x = self->x;
    *(s32 *)&position.y = 0;
    position.z = self->z;
    flags = self->flags;
    if (!(flags & 1)) {
        if (flags & 0x10) {
            if (!(flags & 8)) {
                point[1] = position.x;
                point[0] = position.z;
                spawn_effect_kind_26(&position, 22);
                notify_objects_near_point(self, point, 108.0f, 20.0f, 0xFF);
            }
        } else {
            spawn_effect_kind_26(&position, 5);
        }
        find_objects_in_area(D_803B8254[self->area], 0x100, found, &count);
        for (j = 0; j < count; j++) {
            if ((u32)found[j] >= 4 && D_802C3800[found[j]->kind].handler != 0) {
                D_802C3800[found[j]->kind].handler(found[j], self, 0, message, response);
            }
        }
    }
    if ((*(u32 *)&self->debris & 0xC0000) == 0x40000) {
        spawn_effect_kind_26(&position, 20);
        start_sound_scaled_by_listener_distance(4, position.x, position.z);
    }
    self->flags &= ~8;
    session = get_spawn_session();
    record = &session->objects[self->object];
    if (record->group != -1) {
        ModelGroupRef *group = &session->groups[record->group];
        model = &session->models[group->first + 1];
    } else {
        model = &session->models[record->model];
    }
    list = &session->lists[model->first];
    if (self->debris != 0) {
        for (i = 0; i < list->count; i++) {
            s32 mode = record->flags & 0xF;
            union { u16 half; u32 word; } spinX;
            union { u16 half; u32 word; } spinY;

            mode &= -(mode < 14);
            spinX.word = (u16)(random_u32() % 1280);
            spinY.word = (u16)(random_u32() % 1280);
            spawn_part_debris(&position, 0, record->angle, 0, spinX.word, spinY.word, random_u32() % 1280, self->heading, 0x4000, 0x2000,
                              2.0f, &session->parts[list->first + i], mode, self->flags & 1);
        }
    } else {
        for (i = 0; i < list->count; i++) {
            u8 fade;
            s32 mode = record->flags & 0xF;
            union { u16 half; u32 word; } spinX;
            union { u16 half; u32 word; } spinY;
            union { u16 half; u32 word; } spinZ;
            union { u16 half; u32 word; } heading;

            mode &= -(mode < 14);
            spinX.word = (u16)(random_u32() % 1280);
            spinY.word = (u16)(random_u32() % 1280);
            spinZ.word = (u16)(random_u32() % 1280);
            heading.word = (u16)(random_u32() % 0xFFFF);
            if (!(self->flags & 1)) {
                fade = (random_u32() % (get_difficulty_level() * 8) == 0) << 1;
            } else {
                fade = 1;
            }
            spawn_part_debris(&position, 0, record->angle, 0, spinX.word, spinY.word, spinZ.word, heading.word, 0x2000, 0, 1.0f,
                              &session->parts[list->first + i], mode, fade);
        }
    }
    free_effect_area(self->area);
    *state = 2;
    record->flags &= 0xF;
}
