#include "types.h"

/* LDSYM D_80071EA8=0x80071EA8 */
/* LDSYM D_80071EB0=0x80071EB0 */
/* LDSYM D_80071EB8=0x80071EB8 */
/* LDSYM D_80071EBC=0x80071EBC */
/* LDSYM D_801260A4=0x801260A4 */
/* LDSYM D_801260A5=0x801260A5 */
/* LDSYM D_801260A6=0x801260A6 */
/* LDSYM D_801260A7=0x801260A7 */
/* LDSYM D_803B8238=0x803B8238 */
/* LDSYM D_803B823C=0x803B823C */
/* LDSYM D_803B8248=0x803B8248 */
/* LDSYM D_803B8256=0x803B8256 */
/* LDSYM D_803B8258=0x803B8258 */
/* LDSYM func_8007AAA0=0x8007AAA0 */
/* LDSYM func_800821C0=0x800821C0 */
/* LDSYM func_80085470=0x80085470 */
/* LDSYM func_80085B4C=0x80085B4C */
/* LDSYM func_8008AD10=0x8008AD10 */
/* LDSYM func_8008B89C=0x8008B89C */
/* LDSYM func_80091A60=0x80091A60 */
/* LDSYM func_80092534=0x80092534 */
/* LDSYM func_8009F8EC=0x8009F8EC */
/* LDSYM func_800A03B8=0x800A03B8 */
/* LDSYM func_800A6688=0x800A6688 */
/* LDSYM func_800E19B8=0x800E19B8 */
/* LDSYM func_800ECC1C=0x800ECC1C */
/* LDSYM func_800EDADC=0x800EDADC */
/* LDSYM func_800F3AE0=0x800F3AE0 */
/* LDSYM func_800F3B40=0x800F3B40 */
/* LDSYM func_80107170=0x80107170 */
/* LDSYM func_8010BDA0=0x8010BDA0 */
/* LDSYM func_8010CB4C=0x8010CB4C */

#define NULL ((void *)0)

typedef struct EffectObject {
    u8 flags;
    s8 active;
    u8 pad02[2];
    u32 kind;
    f32 position[3];
    u8 pad14[0x34];
    f32 z;
    f32 x;
    u16 angle;
    s16 group;
    u16 model;
    u8 pad56[2];
} EffectObject;

typedef struct EffectGroup { u8 count; u8 pad01; u16 first; } EffectGroup;
typedef struct EffectModel { u8 count; u8 pad01; u16 first; u8 pad04[8]; } EffectModel;
typedef struct EffectList { u8 count; u8 pad01; u16 first; } EffectList;
typedef struct EffectPart { s32 value00; s32 commands; u16 value08; u8 pad0A[2]; } EffectPart;
typedef union EffectCommand {
    u64 raw;
    struct { u32 w0, w1; } words;
    struct { u8 opcode, pad01; u16 count; void *address; } vertex;
} EffectCommand;
typedef struct EffectVertex { u8 pad00[8]; u16 value08, value0A; u8 pad0C[4]; } EffectVertex;

typedef struct EffectSession {
    u8 pad000[0x568];
    EffectObject *objects;
    EffectGroup *groups;
    EffectModel *models;
    EffectList *lists;
    EffectPart *parts;
    u8 pad57C[4];
    EffectCommand *commands;
} EffectSession;

typedef struct EffectState {
    u32 flags;
    u8 pad04[8];
    union { u32 flagsWord; struct { u8 flags; u8 stages; u8 stage; u8 value0F; } bytes; } mode;
    s16 frame;
    s16 remaining;
    s16 object;
    u8 value16;
    u8 pad17;
    s32 area;
    void *handle;
    s32 handleId;
    void *auxiliary;
} EffectState;

typedef struct EffectKind2BParams {
    s32 mode;
    struct { f32 x, y, z; } position;
    f32 value10;
    f32 value14;
    EffectCommand *displayList;
    s32 lifetime;
    u16 value20;
    u16 value22;
    u16 value24;
    u16 value26;
    u16 value28;
} EffectKind2BParams;

typedef struct AreaPoint { s16 x, y; } AreaPoint;
typedef struct AreaRecord { u8 pad00[0x20]; s16 item; } AreaRecord;
typedef struct NearbyObject { u8 pad00[0x24]; f32 x; u8 pad28[4]; f32 z; } NearbyObject;
typedef struct AuxObject { u8 pad00[4]; s32 id; u8 pad08[0x10]; s32 refs; } AuxObject;
typedef struct SpawnedAux { u8 pad00[0xC]; s32 index; void *start; void *end; } SpawnedAux;
typedef struct SegmentRange { s32 values[10]; } SegmentRange;

extern f64 D_80071EA8, D_80071EB0;
extern f32 D_80071EB8, D_80071EBC;
extern u8 D_801260A4, D_801260A5, D_801260A6, D_801260A7;
extern s32 D_803B8238, D_803B823C;
extern SegmentRange D_803B8248[];
extern u8 D_803B8256[], D_803B8258[];

extern s32 func_8007AAA0(void);
extern EffectSession *func_800821C0(void);
extern void func_80085470(EffectSession *, EffectObject *, s32);
extern void func_80085B4C(s32, f32, f32);
extern SpawnedAux *func_8008AD10(s32, s32, s32);
extern void func_8008B89C(void *);
extern void func_80091A60(s16, EffectCommand *, EffectCommand *, EffectCommand *);
extern void func_80092534(EffectState *);
extern void func_8009F8EC(NearbyObject *, f32, f32);
extern NearbyObject *func_800A03B8(s16);
extern AreaRecord *func_800A6688(u16);
extern void func_800E19B8(u8);
extern void func_800ECC1C(s16, s32, s32, s16, s16, s16, s16, u16, u8);
extern void func_800EDADC(s32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
extern f32 func_800F3AE0(u16);
extern f32 func_800F3B40(u16);
extern void func_80107170(s32);
extern void *func_8010BDA0(EffectKind2BParams *);
extern void func_8010CB4C(void *, s32);

static inline EffectObject *object_at(EffectSession *session, s16 index) {
    return &session->objects[index];
}

void update_effect_kind_5(EffectState *arg0, s32 *arg1) __asm__("func_80092734");

void update_effect_kind_5(EffectState *arg0, s32 *arg1) {
    EffectState *effect;
    EffectKind2BParams config;
    volatile s32 stackPad;
    s32 *volatile state;
    u16 weight;
    EffectSession *session;
    register EffectObject *object __asm__("$18");
    EffectGroup *group;
    EffectModel *currentModel;
    EffectModel *targetModel;
    EffectModel *sourceModel;
    EffectList *current;
    EffectList *target;
    EffectList *source;
    void *start;
    void *end;
    s32 partCount;
    s32 count;
    s32 i;

    state = arg1;
    effect = arg0;
    if (arg0->mode.bytes.flags & 1) {
        s16 worldX = *(s16 *)(D_803B8258 + effect->area * 0x28);
        s16 worldY = *(s16 *)(D_803B8256 + effect->area * 0x28);
        s32 dy = worldY - D_803B8238;
        s32 dx = worldX - D_803B823C;
        i = 0;
        count = func_8007AAA0();
        if (count > 0) {
            f64 divisor = D_80071EA8;
            f64 threshold = D_80071EB0;
            f32 maximum = D_80071EB8;
            f32 scale = D_80071EBC;
            do {
                s16 index = func_800A6688((u16)i)->item;
                if (index != 0xFF) {
                    NearbyObject *nearby = func_800A03B8(index);
                    register f32 x __asm__("$f2") = (f32)dy - nearby->x;
                    register f32 z __asm__("$f0") = (f32)dx - nearby->z;
                    register f64 quotient __asm__("$f0");
                    f32 distance;
                    quotient = (f64)(x*x + z*z);
                    quotient /= divisor;
                    distance = (f32)quotient;
                    if ((f64)distance < threshold) {
                        register f32 amount __asm__("$f2") = (maximum - distance) * scale;
                        func_8009F8EC(nearby, amount, amount);
                    }
                }
                i++;
            } while ((u16)i < count);
        }

        effect->frame++;
        {
            s32 denominator = 0xE10;
            weight = ((denominator - (0x3C - effect->frame) * (0x3C - effect->frame)) << 8) / denominator;
        }
        session = func_800821C0();
        {
            register s32 objectOffset __asm__("$2") =
                effect->object * sizeof(EffectObject);
            register EffectObject *objectBase __asm__("$4") = session->objects;
            object = (EffectObject *)((u8 *)objectBase + objectOffset);
        }
        group = &session->groups[object->group];
        currentModel = &session->models[object->model];
        targetModel = &session->models[group->first + effect->mode.bytes.stage];
        sourceModel = targetModel + 1;
        {
            current = &session->lists[currentModel->first];
            target = &session->lists[targetModel->first];
            source = &session->lists[sourceModel->first];
            partCount = current->count;

            if (effect->frame == 1) {
                if (effect->mode.bytes.stage == 0)
                    func_80092534(effect);
                switch (object->kind) {
                    u8 player;
                    AuxObject *aux;
                case 11: player = D_801260A4; goto add_ref;
                case 12: player = D_801260A5; goto add_ref;
                case 13: player = D_801260A6; goto add_ref;
                case 14: player = D_801260A7;
                add_ref:
                    aux = *(AuxObject **)((u8 *)func_800A6688(player) + 0x1B8);
                    if (aux != NULL) aux->refs++;
                    break;
                }
                object->active = 1;
                if (effect->handle != NULL) {
                    AuxObject *handle = effect->handle;
                    if (handle->id == effect->handleId) func_8010CB4C(handle, 0);
                    effect->handle = NULL;
                }
                if (effect->mode.bytes.stage == effect->mode.bytes.stages - 2 &&
                    (effect->mode.flagsWord & 0x0C000000)) {
                    SpawnedAux *spawned;
                    s32 index = group->first + group->count;
                    index--;
                    start = (u8 *)object + 8;
                    end = (u8 *)object + 0x48;
                    spawned = func_8008AD10(0, 0x13, 0x18);
                    if (spawned == NULL) {
                        spawned = NULL;
                    } else {
                        spawned->index = index;
                        spawned->start = start;
                        spawned->end = end;
                    }
                    effect->auxiliary = spawned;
                }
                i = 0;
                if (partCount != 0) do {
                        register s32 srcIndex __asm__("$3");
                        register s32 dstIndex __asm__("$4");
                        register EffectPart *parts __asm__("$5");
                        register volatile EffectPart *src __asm__("$6");
                        register volatile EffectPart *dst __asm__("$7");
                        register s32 srcValue __asm__("$3");
                        register u16 srcHalf __asm__("$2");
                        register s32 dstOffset __asm__("$2");
                        register EffectCommand *srcCommands __asm__("$8");
                        register EffectCommand *dstCommands __asm__("$9");
                        register u32 outerSentinel __asm__("$12") = 0xB8000000;
                        register u32 vertexOpcode __asm__("$11") = 4;
                        srcIndex = source->first;
                        dstIndex = current->first;
                        parts = session->parts;
                        srcIndex += i;
                        src = &parts[srcIndex];
                        dstIndex += i;
                        dstOffset = dstIndex * 3;
                        __asm__ volatile ("" : : : "memory");
                        srcValue = src->value00;
                        dstOffset *= 4;
                        dst = (EffectPart *)((u8 *)parts + dstOffset);
                        dst->value00 = srcValue;
                        srcHalf = src->value08;
                        dst->value08 = srcHalf;
                        srcCommands = &session->commands[src->commands];
                        dstCommands = &session->commands[dst->commands];
                        {
                        if (srcCommands->words.w0 != outerSentinel) {
                            register u32 sentinel __asm__("$10") = 0xB8000000;
                            register EffectCommand *command __asm__("$7") = srcCommands;
                            do {
                                if (command->vertex.opcode == vertexOpcode) {
                                    EffectVertex *srcVertices = command->vertex.address;
                                    EffectVertex *dstVertices = (EffectVertex *)((u8 *)dstCommands +
                                                      ((u8 *)srcVertices - (u8 *)&session->commands[src->commands]));
                                    s32 n = (command->vertex.count >> 10);
                                    s32 j = 0;
                                    if (n != 0) do {
                                        dstVertices[j].value08 = srcVertices[j].value08;
                                        dstVertices[j].value0A = srcVertices[j].value0A;
                                        j++;
                                    } while (j < n);
                                }
                                command++;
                            } while (command->words.w0 != sentinel);
                        }
                        }
                        i++;
                    } while (i < partCount);
                if (!(effect->mode.bytes.flags & 0x10)) {
                    SegmentRange *range = &D_803B8248[effect->area];
                    func_800EDADC(range->values[0], range->values[1], range->values[2], range->values[3],
                                  range->values[4], range->values[5], range->values[6], range->values[7],
                                  range->values[8], range->values[9]);
                    func_80085B4C(0, object->x, object->z);
                }
            }

            i = 0;
            if (partCount != 0) do {
                    register EffectPart *parts __asm__("$6");
                    EffectCommand *commands;
                    register EffectPart *pc __asm__("$7");
                    register EffectPart *pf __asm__("$3");
                    register s32 callWeight __asm__("$4");
                    s32 pcCommand;
                    register s32 pfCommand __asm__("$5");
                    register s32 ptCommand __asm__("$6");
                    register s32 pcOffset __asm__("$3");
                    register s32 ptOffset __asm__("$2");

                    callWeight = (s16)weight;
                    parts = session->parts;
                    pcOffset = (current->first + i) * 12;
                    pc = (EffectPart *)((u8 *)parts + pcOffset);
                    pf = &parts[target->first + i];
                    pcCommand = pc->commands;
                    ptOffset = (source->first + i) * 12;
                    pfCommand = pf->commands;
                    parts = (EffectPart *)((u8 *)parts + ptOffset);
                    ptCommand = parts->commands;
                    commands = session->commands;
                    func_80091A60(callWeight, &commands[pfCommand],
                                  &commands[ptCommand], &commands[pcCommand]);
                    i++;
                } while (i < partCount);

            if (effect->frame == 15 && partCount < source->count &&
                (effect->mode.bytes.flags & 0x40) && effect->remaining > 0) {
                volatile u8 unusedStack[20];
                EffectPart *part =
                    (EffectPart *)((source->first + source->count) * sizeof(EffectPart) +
                                   (u32)session->parts);
                EffectCommand *commands = &session->commands[(part - 1)->commands];
                f32 cosAngle;
                config.mode = 1;
                config.position.x = object->x;
                config.position.y = 0;
                config.position.z = object->z;
                config.value10 = func_800F3AE0(object->angle);
                cosAngle = func_800F3B40(object->angle);
                config.value14 = cosAngle;
                config.displayList = commands;
                config.lifetime = -1;
                config.value22 = 100;
                config.value20 = 100;
                config.value24 = 30;
                config.value26 = 16000;
                config.value28 = 60;
                effect->handle = func_8010BDA0(&config);
                if (effect->handle != NULL)
                    effect->handleId = ((AuxObject *)effect->handle)->id;
            }
        }

        if (effect->frame == 60) {
            effect->frame = 0;
            effect->mode.bytes.stage++;
            if (effect->mode.bytes.stage == effect->mode.bytes.stages - 1) {
                func_800E19B8(effect->mode.bytes.value0F);
                if (effect->auxiliary != NULL) {
                    func_8008B89C(effect->auxiliary);
                    effect->auxiliary = NULL;
                }
                if (effect->mode.bytes.flags & 8) {
                    session = func_800821C0();
                    {
                        register s32 objectOffset __asm__("$2");
                        objectOffset = effect->object * sizeof(EffectObject);
                        object = (EffectObject *)((u8 *)session->objects + objectOffset);
                    }
                    group = &session->groups[object->group];
                    object->model = group->first + effect->mode.bytes.stage + 1;
                    object->kind = 0x1D;
                    currentModel = &session->models[object->model];
                    func_80107170(effect->area);
                    func_800ECC1C(effect->object, (s32)object->x, (s32)object->z,
                                  *(s16 *)((u8 *)currentModel + 4), *(s16 *)((u8 *)currentModel + 8),
                                  *(s16 *)((u8 *)currentModel + 6), *(s16 *)((u8 *)currentModel + 10),
                                  object->angle, effect->value16);
                    *state = 2;
                    return;
                } else {
                    if (effect->mode.bytes.flags & 4) {
                        session = func_800821C0();
                        {
                            register s32 objectOffset __asm__("$2");
                            objectOffset = effect->object * sizeof(EffectObject);
                            object = (EffectObject *)((u8 *)session->objects + objectOffset);
                        }
                        group = &session->groups[object->group];
                        object->model = group->first + effect->mode.bytes.stage + 1;
                        object->kind = 0x1C;
                    }
                    func_80107170(effect->area);
                    *state = 2;
                    goto finish;
                }
            }
        finish:
            if (effect->remaining > 0) {
                effect->mode.bytes.flags &= 0x6F;
                goto active;
            }
        }
    } else {
        if (effect->mode.bytes.stage < effect->mode.bytes.stages - 1) {
            effect->mode.bytes.stage++;
            session = func_800821C0();
            {
                register s32 objectOffset __asm__("$2");
                objectOffset = effect->object * sizeof(EffectObject);
                object = (EffectObject *)((u8 *)session->objects + objectOffset);
            }
            group = &session->groups[object->group];
            object->model = group->first + effect->mode.bytes.stage;
            if (effect->mode.bytes.flags & 2) func_80085470(session, object, effect->area);
        }
    active:
        *state = 1;
    }
}
