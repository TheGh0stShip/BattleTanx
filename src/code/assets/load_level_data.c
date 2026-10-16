#include "types.h"

#define NULL 0
#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern void rom_dma_read() __asm__("func_80077930");
extern s32 get_difficulty_level() __asm__("func_8007AAA0");
extern s32 get_entity_capacity() __asm__("func_8007AAB0");
extern s32 get_game_mode() __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6() __asm__("func_8007C6D8");
extern s32 runtime_mode_accepts_input() __asm__("func_8007C728");
extern s32 get_state_slot_value() __asm__("func_8007D1F8");
extern void set_runtime_rgb_bytes() __asm__("func_8007D430");
extern void get_runtime_rgb_bytes() __asm__("func_8007D48C");
extern s32 get_runtime_byte_setting() __asm__("func_80081A30");
extern void set_runtime_byte_setting() __asm__("func_80081A40");
extern void func_80085290();
extern void offset_display_list_image_addresses() __asm__("func_800852E0");
extern void rewrite_display_list_commands() __asm__("func_80085330");
extern void scale_display_list_vertex_colors(s32 commands, f32 scale) __asm__("func_80086DC0");
extern s32 plan_bank_record_resources() __asm__("func_8008785C");
extern void swap_player_skin_textures() __asm__("func_80087D30");
extern s16 copy_model_node() __asm__("func_80088360");
extern void spawn_bank_record_entries() __asm__("func_80088670");
extern void walk_effect_lists() __asm__("func_8008B080");
extern void func_800907CC();
extern void spawn_effect_kind_09() __asm__("func_80091D6C");
extern void *spawn_effect_kind_5() __asm__("func_80091E98");
extern void matrix_identity() __asm__("func_800A7650");
extern void set_model_transform(void *xf, f32 x, f32 z, s32 angle) __asm__("func_800A76BC");
extern void transform_point_3x4() __asm__("func_800A7D10");
extern s8 advance_wrapped_byte() __asm__("func_800DDB94");
extern void clear_level_input_flags(void) __asm__("func_800DDBCC");
extern void clear_runtime_status_byte() __asm__("func_800E19B8");
extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");
extern void func_800ECC1C();
extern void spawn_effect_kind_6(f32 x, f32 z, s32 slot, s32 value14, s32 value28, s32 flags) __asm__("func_800EF984");
extern void spawn_slot_effect_kind_21(f32 x, f32 y, s32 slot, s32 id, s32 minX, s32 maxX, s32 minY, s32 maxY) __asm__("func_800F05F4");
extern void spawn_color_effect() __asm__("func_800F3014");
extern s32 lzari_decode() __asm__("func_800F4F60");
extern void init_runtime_flag_records(s32 width, s32 height) __asm__("func_80106B60");
extern void func_80106D18();
extern void spawn_effect_kind_1c(void *owner, s32 flags, f32 x, f32 z, s32 angle, s32 param) __asm__("func_8010D480");
extern void bzero() __asm__("func_80110C00");
extern void osGetTime() __asm__("func_801120A0");
extern void guMtxF2L() __asm__("func_801146A0");
extern float sqrtf(float);

typedef struct { f32 v[4][3]; } LevelCorners;
extern const LevelCorners sBoxCornerTemplate __asm__("D_80071864");
extern const f32 sBoxMargin __asm__("D_80071894");
extern f32 gLevelFogScale[] __asm__("D_8012596C");
typedef struct { u8 r, g, b; } LevelColor;
extern LevelColor gLevelColors[] __asm__("D_801259DC");
typedef struct { u32 start; u32 end; u32 pad8; u32 padC; } LevelRomRange;
extern LevelRomRange gLevelRomRanges[] __asm__("D_80125A68");
extern f32 gCurrentFogScale __asm__("D_80125C30");
extern u8 gTeamStateSlots[] __asm__("D_801260A4");
extern u8 gDemoModeFlag __asm__("D_8013576B");
extern u8 gAttractModeFlag __asm__("D_80135771");
extern s8 gLevelLoadedFlag __asm__("D_80135820");
extern s16 gLinkBoxIds __asm__("D_802D5A30");
extern u8 gLevelTextureRom[] __asm__("D_B03EA970");
extern u8 gLevelModelRom[] __asm__("D_B05A1110");

typedef struct { s32 w[4]; } Quad16;
typedef struct { u8 active; u8 pad1[3]; f32 z0; f32 x0; f32 z1; f32 x1; } LevelSpawn;
typedef struct { s32 w[15]; } Blk3C;
typedef struct { s32 w[30]; } Blk78;
typedef struct { s32 w[45]; } BlkB4;
typedef struct { s32 w[60]; } BlkF0;

typedef struct {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 kind;
    /* 0x02 */ u8 param;
    /* 0x03 */ u8 attr;
    /* 0x04 */ u16 id;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 type;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 z;
    /* 0x14 */ u16 angle;
    /* 0x16 */ s16 link;
    /* 0x18 */ s16 box;
    /* 0x1A */ u8 pad1A[2];
} LevelObject;

typedef struct {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s16 x0;
    /* 0x6 */ s16 z0;
    /* 0x8 */ s16 x1;
    /* 0xA */ s16 z1;
} LevelBox;

typedef struct {
    /* 0x00 */ void *info;
    /* 0x04 */ void *groups;
    /* 0x08 */ LevelObject *objects;
    /* 0x0C */ LevelBox *boxes;
    /* 0x10 */ void *table10;
    /* 0x14 */ void *table14;
    /* 0x18 */ void *table18;
    /* 0x1C */ void *table1C;
    /* 0x20 */ u32 count20;
    /* 0x24 */ void *buffer;
    /* 0x28 */ void *work;
} LevelHeader;

typedef struct {
    /* 0x000 */ Quad16 bounds0;
    /* 0x010 */ Quad16 bounds1;
    /* 0x020 */ u8 pad20[0xC4 - 0x20];
    /* 0x0C4 */ s32 infoFlags;
    /* 0x0C8 */ LevelSpawn spawns[4];
    /* 0x118 */ Blk3C block118;
    /* 0x154 */ Blk78 block154;
    /* 0x1CC */ BlkB4 block1CC;
    /* 0x280 */ BlkF0 block280;
    /* 0x370 */ u8 pad370[0x564 - 0x370];
    /* 0x564 */ s32 groups;
    /* 0x568 */ s32 objects;
    /* 0x56C */ s32 links;
    /* 0x570 */ s32 boxes;
    /* 0x574 */ s32 table574;
    /* 0x578 */ s32 table578;
    /* 0x57C */ s32 table57C;
    /* 0x580 */ s32 table580;
    /* 0x584 */ u8 pad584[0x634 - 0x584];
    /* 0x634 */ s32 groupCount;
    /* 0x638 */ s32 firstGroup;
} LevelRuntime;

typedef struct { s32 rom; s32 size; s32 dest; s32 padC; } LevelChunk;
typedef struct { s32 id; s32 used; } LevelSlotRef;
typedef struct { s32 rom; u16 flags; u8 pad6[2]; s32 rom2; s32 padC; } LevelChunkRef;
typedef struct { s32 a; s32 b; s16 c; u8 padA[2]; } LevelSlot;
typedef struct {
    /* 0x0000 */ u8 pad0[4];
    /* 0x0004 */ s32 boxCount;
    /* 0x0008 */ LevelSlotRef boxRefs[0x1C2];
    /* 0x0E18 */ s32 linkCount;
    /* 0x0E1C */ LevelSlotRef linkRefs[0x40];
    /* 0x101C */ u8 pad101C[4];
    /* 0x1020 */ s32 table574Count;
    /* 0x1024 */ LevelSlotRef table574Refs[0x258];
    /* 0x22E4 */ u8 pad22E4[4];
    /* 0x22E8 */ s32 slotCount;
    /* 0x22EC */ LevelSlotRef slots[0xE10];
    /* 0x936C */ s32 chunkCount;
    /* 0x9370 */ LevelChunk chunks[0x100];
    /* 0xA370 */ s32 chunk2Size;
    /* 0xA374 */ s32 chunk2Count;
    /* 0xA378 */ LevelChunk chunks2[1];
} LevelWork;
static inline s32 find_chunk(LevelWork *w, s32 key) {
    s32 i;
    for (i = 0; i < w->chunkCount; i++) {
        if (w->chunks[i].rom == key) {
            return i;
        }
    }
    return 0;
}
static inline s32 find_chunk2(LevelWork *w, s32 key) {
    s32 i;
    for (i = 0; i < w->chunk2Count; i++) {
        if (w->chunks2[i].rom == key) {
            return i;
        }
    }
    return 0;
}

s32 load_level_data(s32 levelIndex, LevelRuntime *runtimeBuf, s32 runtimeBufSize, void *packed, s32 packedSize, LevelHeader *header, u32 headerBufSize, s32 skinSlots) __asm__("func_80088CF0");

s32 load_level_data(s32 levelIndex, LevelRuntime *runtimeBuf, s32 runtimeBufSize, void *packed, s32 packedSize, LevelHeader *header, u32 headerBufSize, s32 skinSlots) {
    s32 level;
    void *work;
    s32 needed;
    s32 j;
    s32 objIndex;
    s32 gameMode;
    void *group;
    LevelRuntime *rt;
    LevelHeader *hdr;
    s32 baseSize;
    u8 blue;
    u8 green;
    u8 red;
    f32 mtx[4][4];
    s32 byteSetting;

    s16 *linkBoxId;
    s32 entryOffset;
    s32 objType;
    s32 objType2;
    s32 objCount;
    s32 total;
    s32 groupsAt;
    s32 objectsAt;
    s32 boxesAt;
    s32 linksAt;
    s32 table574At;
    s32 table578At;
    s32 table57CAt;
    s32 boxOffset;
    s32 i;
    s32 k2;
    s8 statusByte;
    s8 stateBits;
    u32 count20;
    u8 *objByte;
    u8 slotValue2;
    u8 slotValue;
    u8 objFlags2;
    u8 objFlags;
    void *romStart;
    void *boxSrc;
    void *effect;
    LevelObject *obj;
    void *groupOut;
    void *workBuf;
    void *linkSrc;
    void *entrySrc;

    level = levelIndex;
    gameMode = get_game_mode();
    osGetTime();
    gLevelLoadedFlag = 0;
    gCurrentFogScale = gLevelFogScale[level];
    objIndex = 0;
    set_runtime_rgb_bytes(gLevelColors[level].r, gLevelColors[level].g, gLevelColors[level].b);
    if (headerBufSize < 0x1143CU) {
        return -1;
    }
    {
        hdr = header;
        bzero(hdr, 0x1143C);
        workBuf = (u8 *) hdr + 0x2C;
        hdr->work = workBuf;
        romStart = (void *) gLevelRomRanges[level].start;
        work = workBuf;
        rom_dma_read(romStart, runtimeBuf, ((gLevelRomRanges[level].end - (u32) romStart) + 7) & ~7);
        if (lzari_decode(gLevelRomRanges[level].end - gLevelRomRanges[level].start, runtimeBuf, packedSize, packed) < 0) {
            return -1;
        }
        {
            hdr->buffer = packed;
            hdr->info = (void *) (packed + FIELD(packed, s32 *, 0));
            hdr->groups = (void *) (packed + FIELD(packed, s32 *, 4));
            ((void *) hdr->objects) = (void *) (packed + FIELD(packed, s32 *, 8));
            hdr->table10 = (void *) (packed + FIELD(packed, s32 *, 0x10));
            ((void *) hdr->boxes) = (void *) (packed + FIELD(packed, s32 *, 0xC));
            hdr->table14 = (void *) (packed + FIELD(packed, s32 *, 0x14));
            hdr->table18 = (void *) (packed + FIELD(packed, s32 *, 0x18));
            hdr->table1C = (void *) (packed + FIELD(packed, s32 *, 0x1C));
            hdr->count20 = (u32) ((u32) (FIELD(packed, s32 *, 0x20) - FIELD(packed, s32 *, 0x1C)) >> 4);
            if (game_mode_is_3_through_6() != 0) {
                switch (level) {
                case 11:
                    goto set_byte_setting;
                case 12:
                case 14:
                    byteSetting = 1;
                    break;
                default:
                    byteSetting = 1;
                    break;
                }
            } else {
                byteSetting = 0;
                if (FIELD(hdr->info, s32 *, 0x20) & 1) {
set_byte_setting:
                    byteSetting = 1;
                }
            }
            set_runtime_byte_setting(byteSetting);
            swap_player_skin_textures(hdr, 0, skinSlots);
            osGetTime();
            objCount = plan_bank_record_resources(hdr, 0);
            if (objCount < 0) {
                return -1;
            }
            {
                osGetTime();
                baseSize = sizeof(LevelRuntime);
                total = (FIELD(hdr->info, s32 *, 0x27C) * 0x18) + ((objCount * 0x58) + baseSize) + (FIELD(work, s32 *, 4) * 0xC) + (FIELD(work, s32 *, 0xE18) * 4) + (FIELD(work, s32 *, 0x1020) * 4) + (FIELD(work, s32 *, 0x22E8) * 0xC) + FIELD(work, s32 *, 0xA370) + FIELD(work, s32 *, 0x113FC) + 0x40;
                needed = total;
                if (runtimeBufSize < total) {
                    return -1;
                }
                bzero(runtimeBuf, needed);
                rt = runtimeBuf;
                rt->bounds0 = FIELD(hdr->info, Quad16 *, 0);
                rt->bounds1 = FIELD(hdr->info, Quad16 *, 0x10);
                rt->infoFlags = (s32) FIELD(hdr->info, s32 *, 0x20);
                init_runtime_flag_records((s32) -FIELD(rt, f32 *, 0x10), (s32) -FIELD(rt, f32 *, 0x14));
                count20 = hdr->count20;
                for (k2 = 0; k2 < (s32) count20; k2++) {
                }
                rt->groupCount = (s32) FIELD(hdr->info, s32 *, 0x27C);
                rt->firstGroup = 0;
                rt->block118 = FIELD(hdr->info, Blk3C *, 0x24);
                rt->block154 = FIELD(hdr->info, Blk78 *, 0x60);
                rt->block1CC = FIELD(hdr->info, BlkB4 *, 0xD8);
                rt->block280 = FIELD(hdr->info, BlkF0 *, 0x18C);
                groupsAt = (s32) ((u8 *) runtimeBuf + 0x643) & ~7;
                rt->groups = groupsAt;
                objectsAt = (groupsAt + (FIELD(hdr->info, s32 *, 0x27C) * 0x18) + 7) & ~7;
                rt->objects = objectsAt;
                boxesAt = (objectsAt + (objCount * 0x58) + 7) & ~7;
                rt->boxes = boxesAt;
                linksAt = (boxesAt + (FIELD(work, s32 *, 4) * 0xC) + 7) & ~7;
                rt->links = linksAt;
                table574At = (linksAt + (FIELD(work, s32 *, 0xE18) * 4) + 7) & ~7;
                rt->table574 = table574At;
                table578At = (table574At + (FIELD(work, s32 *, 0x1020) * 4) + 7) & ~7;
                rt->table578 = table578At;
                i = 0;
                table57CAt = (table578At + (FIELD(work, s32 *, 0x22E8) * 0xC) + 7) & ~7;
                rt->table57C = table57CAt;
                linkBoxId = &gLinkBoxIds;
                rt->table580 = (s32) ((table57CAt + FIELD(work, s32 *, 0xA370) + 7) & ~7);
                do {
                    if (*linkBoxId != -1) {
                        *linkBoxId = ((LevelWork *) work)->boxRefs[i + FIELD(hdr->info, s32 *, 0x2DC)].id;
                    }
                    i += 1;
                    linkBoxId += 1;
                } while (i < 0xB6);
                for (i = 0; i < 0x40; i++) {
                    if (((LevelWork *) work)->linkRefs[i].used == 0) {
                        continue;
                    }
                    linkSrc = hdr->table10 + (i * 4);
                    *(u8 *)((((LevelWork *) work)->linkRefs[i].id * 4) + rt->links) = FIELD(linkSrc, u8 *, 0);
                    FIELD(((((LevelWork *) work)->linkRefs[i].id * 4) + rt->links), s16 *, 2) = ((LevelWork *) work)->boxRefs[FIELD(linkSrc, u16 *, 2)].id;
                }
                i = 0;
                for (i = 0; i < rt->groupCount; i++) {
                    {
                        group = (u8 *) hdr->groups + ((FIELD(hdr->info, s32 *, 0x280) != -1) ? (i + 1) : i) * 0x14;
                        *(u8 *)((s32)(i * 0x18) + rt->groups) = (s8) FIELD(group, u16 *, 0);
                        FIELD(((i * 0x18) + rt->groups), u16 *, 2) = objIndex;
                        groupOut = (i * 0x18) + rt->groups;
                        FIELD(groupOut, Quad16 *, 4) = FIELD(group, Quad16 *, 4);
                        FIELD(((i * 0x18) + rt->groups), s32 *, 0x14) = (s32) ((s32) (FIELD(group, f32 *, 4) + FIELD(group, f32 *, 0xC)) / 2);
                        {
                            for (j = 0; j < *(u8 *)((s32)(i * 0x18) + rt->groups); j++) {
                                obj = &hdr->objects[FIELD(group, u16 *, 2) + j];
                                *(u8 *)((s32)(objIndex * 0x58) + rt->objects) = obj->kind;
                                FIELD(((objIndex * 0x58) + rt->objects), u8 *, 1) = (u8) obj->attr;
                                FIELD(((objIndex * 0x58) + rt->objects), s32 *, 4) = (s32) obj->type;
                                FIELD(((objIndex * 0x58) + rt->objects), f32 *, 0x4C) = (f32) FIELD(obj, f32 *, 0xC);
                                FIELD(((objIndex * 0x58) + rt->objects), f32 *, 0x48) = (f32) FIELD(obj, f32 *, 0x10);
                                FIELD(((objIndex * 0x58) + rt->objects), u16 *, 0x50) = (u16) obj->angle;
                                if (!(obj->attr & 0x80) && (rt->firstGroup == 0)) {
                                    rt->firstGroup = i;
                                }
                                matrix_identity(mtx);
                                set_model_transform(mtx, FIELD(obj, f32 *, 0xC), FIELD(obj, f32 *, 0x10), obj->angle);
                                guMtxF2L(mtx, rt->objects + (objIndex * 0x58) + 8);
                                if (obj->link == -1) {
                                    FIELD(((objIndex * 0x58) + rt->objects), s16 *, 0x52) = -1;
                                } else {
                                    FIELD(((objIndex * 0x58) + rt->objects), s16 *, 0x52) = ((LevelWork *) work)->linkRefs[obj->link].id;
                                }
                                if (obj->flags & 1) {
                                    FIELD(((objIndex * 0x58) + rt->objects), s16 *, 0x54) = copy_model_node(hdr, rt, obj->box);
                                } else {
                                    FIELD(((objIndex * 0x58) + rt->objects), s16 *, 0x54) = ((LevelWork *) work)->boxRefs[obj->box].id;
                                }
                                {
                                    LevelCorners corners = sBoxCornerTemplate;
                                    f32 world[4][3];
                                    f32 flat[4][2];
                                    f32 d;
                                    s32 k;
                                    corners.v[0][0] = (hdr->boxes[obj->box].x0);
                                    corners.v[0][2] = (hdr->boxes[obj->box].z0);
                                    corners.v[1][0] = (hdr->boxes[obj->box].x1);
                                    corners.v[1][2] = (hdr->boxes[obj->box].z0);
                                    corners.v[2][0] = (hdr->boxes[obj->box].x1);
                                    corners.v[2][2] = (hdr->boxes[obj->box].z1);
                                    corners.v[3][0] = (hdr->boxes[obj->box].x0);
                                    corners.v[3][2] = (hdr->boxes[obj->box].z1);
                                    for (k = 0; k < 4; k++) {
                                        transform_point_3x4(mtx, corners.v[k], world[k]);
                                        flat[k][1] = world[k][0];
                                        flat[k][0] = world[k][2];
                                    }
#define CLEN(i) sqrtf(corners.v[i][0] * corners.v[i][0] + corners.v[i][2] * corners.v[i][2])
#define CMAX(a, b) ((a) > (b) ? (a) : (b))
                                    d = CMAX(CMAX(CLEN(0), CLEN(1)), CMAX(CLEN(2), CLEN(3)));
#undef CLEN
#undef CMAX
                                }
                                if (((obj->flags & 0x10) && (game_mode_is_3_through_6() == 0)) || ((obj->flags & 0x40) && (game_mode_is_3_through_6() != 0)) || ((obj->flags & 2) && (((runtime_mode_accepts_input() == 0) && (audio_restarts_disabled() == 0)) || ((objFlags2 = obj->flags, ((objFlags2 & 2) != 0)) && (slotValue2 = gTeamStateSlots[(objFlags2 & 0xC) >> 2], (((s32) slotValue2 < get_entity_capacity()) == 0)))))) {
                                    *(u8 *)((s32)(objIndex * 0x58) + rt->objects) = 0;
                                    switch (FIELD(((objIndex * 0x58) + rt->objects), u32 *, 4)) {
                                    case 5:
                                    case 11:
                                    case 12:
                                    case 13:
                                    case 14:
                                    case 20:
                                        clear_runtime_status_byte(advance_wrapped_byte(0xF) & 0xFF);
                                        break;
                                    }
                                } else {
                                    *(u8 *)((s32)(objIndex * 0x58) + rt->objects) = obj->kind;
                                    if (obj->flags & 2) {
                                        objByte = (objIndex * 0x58) + rt->objects;
                                        *objByte &= 0xF0;
                                        stateBits = get_state_slot_value(gameMode, gTeamStateSlots[(obj->flags & 0xC) >> 2]);
                                        *(u8 *)((objIndex * 0x58) + rt->objects) |= stateBits;
                                    }
                                    if (get_difficulty_level() >= 3) {
                                        objType = FIELD(((objIndex * 0x58) + rt->objects), s32 *, 4);
                                        switch (objType) {
                                        case 3:
                                        case 6:
                                        case 9:
                                        case 15:
                                        case 18:
                                            *(u8 *)((s32)(objIndex * 0x58) + rt->objects) = 0;
                                            FIELD(((objIndex * 0x58) + rt->objects), s32 *, 4) = 7;
                                            break;
                                        }
                                    }
                                    objType2 = FIELD(((objIndex * 0x58) + rt->objects), s32 *, 4);
                                    switch (objType2) {
                                    case 16:
                                        rt->spawns[obj->param].active = 1;
                                        rt->spawns[obj->param].x0 = (f32) FIELD(obj, f32 *, 0xC);
                                        rt->spawns[obj->param].z0 = (f32) FIELD(obj, f32 *, 0x10);
                                        break;
                                    case 17:
                                        rt->spawns[obj->param].active = 1;
                                        rt->spawns[obj->param].x1 = (f32) FIELD(obj, f32 *, 0xC);
                                        rt->spawns[obj->param].z1 = (f32) FIELD(obj, f32 *, 0x10);
                                        break;
                                    case 3:
                                        spawn_effect_kind_6(FIELD(obj, f32 *, 0xC), FIELD(obj, f32 *, 0x10), objIndex, obj->angle, 0xEA, (s32) obj->param);
                                        break;
                                    case 1:
                                        func_80106D18(0, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) ((f32) hdr->boxes[obj->box].x0 - sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].x1 + sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].z0 - sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].z1 + sBoxMargin), 0xF85F, obj->angle);
                                        break;
                                    case 30:
                                        func_80106D18(2, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), hdr->boxes[obj->box].x0, hdr->boxes[obj->box].x1, hdr->boxes[obj->box].z0, hdr->boxes[obj->box].z1, 0xF85F, obj->angle);
                                        break;
                                    case 26:
                                        func_80106D18(1, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), hdr->boxes[obj->box].x0, hdr->boxes[obj->box].x1, hdr->boxes[obj->box].z0, hdr->boxes[obj->box].z1, 0xF85F, obj->angle);
                                        break;
                                    case 19:
                                    case 27:
                                        func_80106D18(0, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) ((f32) hdr->boxes[obj->box].x0 - sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].x1 + sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].z0 - sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].z1 + sBoxMargin), 0x1A, obj->angle);
                                        break;
                                    case 8:
                                        func_800ECC1C(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) ((f32) hdr->boxes[obj->box].x0 - sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].x1 + sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].z0 - sBoxMargin), (s32) ((f32) hdr->boxes[obj->box].z1 + sBoxMargin), (s32) obj->angle, 0);
                                        break;
                                    case 21:
                                        *(u8 *)((s32)(objIndex * 0x58) + rt->objects) = 0;
                                        if (get_difficulty_level() == 1) {
                                            spawn_effect_kind_1c(NULL, obj->id, FIELD(obj, f32 *, 0xC), FIELD(obj, f32 *, 0x10), (s32) obj->angle, (s32) obj->param);
                                        }
                                        break;
                                    case 20:
                                        effect = spawn_effect_kind_5(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, (s32) obj->angle, 1, 0);
                                        stateBits = advance_wrapped_byte(0xF);
                                        FIELD(effect, s8 *, 0xF) = stateBits;
                                        clear_runtime_status_byte(stateBits & 0xFF);
                                        if (game_mode_is_3_through_6() != 0) {
                                            spawn_effect_kind_1c(effect, obj->id, FIELD(obj, f32 *, 0xC), FIELD(obj, f32 *, 0x10), (s32) obj->angle, (s32) obj->param);
                                        }
                                        break;
                                    case 11:
                                    case 12:
                                    case 13:
                                    case 14:
                                        statusByte = advance_wrapped_byte(0xF);
                                        objFlags = obj->flags;
                                        if ((objFlags & 2) && (slotValue = gTeamStateSlots[(objFlags & 0xC) >> 2], (((s32) slotValue < get_entity_capacity()) == 0))) {
                                            *(u8 *)((s32)(objIndex * 0x58) + rt->objects) = 0;
                                            clear_runtime_status_byte(statusByte & 0xFF);
                                        } else {
                                            FIELD(spawn_effect_kind_5(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, (s32) obj->angle, (s32) obj->param, 0), s8 *, 0xF) = statusByte;
                                        }
                                        break;
                                    case 5:
                                        FIELD(spawn_effect_kind_5(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, (s32) obj->angle, (s32) obj->param, 0), s8 *, 0xF) = advance_wrapped_byte(0xF);
                                        break;
                                    case 31:
                                        FIELD(spawn_effect_kind_5(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, (s32) obj->angle, (s32) obj->param, 1), s8 *, 0xF) = advance_wrapped_byte(0xF);
                                        break;
                                    case 6:
                                        if (obj->param & 0x10) {
                                            spawn_slot_effect_kind_21(FIELD(obj, f32 *, 0xC), FIELD(obj, f32 *, 0x10), objIndex, obj->angle, (s32) hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1);
                                        } else {
                                            spawn_effect_kind_09(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, (s32) obj->angle, (s32) obj->param);
                                        }
                                        break;
                                    case 15:
                                        func_800907CC(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) obj->angle, (s32) hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, 1);
                                        break;
                                    case 9:
                                        func_800907CC(objIndex, (s32) FIELD(obj, f32 *, 0xC), (s32) FIELD(obj, f32 *, 0x10), (s32) obj->angle, (s32) hdr->boxes[obj->box].x0, (s32) hdr->boxes[obj->box].x1, (s32) hdr->boxes[obj->box].z0, (s32) hdr->boxes[obj->box].z1, (s32) obj->param);
                                        break;
                                    }
                                }
                                objIndex += 1;
                            }
                        }

                    }
                }
                i = 0;
                boxOffset = 0;
                do {
                    if (((LevelWork *) work)->boxRefs[i].used != 0) {
                        s32 id = ((LevelWork *) work)->boxRefs[i].id;
                        boxSrc = ((void *) hdr->boxes) + boxOffset;
                        FIELD(id * 0xC + rt->boxes, u8 *, 0) = FIELD(boxSrc, u8 *, 0);
                        FIELD(id * 0xC + rt->boxes, s16 *, 2) = ((LevelWork *) work)->table574Refs[FIELD(boxSrc, u16 *, 2)].id;
                        FIELD(id * 0xC + rt->boxes, u16 *, 4) = FIELD(boxSrc, u16 *, 4);
                        FIELD(id * 0xC + rt->boxes, u16 *, 6) = FIELD(boxSrc, u16 *, 6);
                        FIELD(id * 0xC + rt->boxes, u16 *, 8) = FIELD(boxSrc, u16 *, 8);
                        FIELD(id * 0xC + rt->boxes, u16 *, 0xA) = FIELD(boxSrc, u16 *, 0xA);
                    }
                    boxOffset += 0xC;
                    i += 1;
                } while (i < 0x1C2);
                i = 0;
                for (; i < 0x258; i++) {
                    if (((LevelWork *) work)->table574Refs[i].used == 0) {
                        continue;
                    }
                    entryOffset = ((LevelWork *) work)->table574Refs[i].id * 4;
                    entrySrc = hdr->table14 + (i * 4);
                    *(u8 *)((s32)entryOffset + rt->table574) = FIELD(entrySrc, u8 *, 0);
                    FIELD((entryOffset + rt->table574), s16 *, 2) = ((LevelWork *) work)->slots[FIELD(entrySrc, u16 *, 2)].id;
                }
                {
                    LevelWork *w;
                    for (i = 0, w = work; i < 0xE10; i++) {
                        if (w->slots[i].used != 0) {
                            s32 id = w->slots[i].id;
                            LevelChunkRef *rec = &((LevelChunkRef *) hdr->table18)[i];
                            s32 a = find_chunk(hdr->work, rec->rom);
                            s32 b = find_chunk2(hdr->work, rec->rom2);
                            u16 f;
                            (*(LevelSlot *) (id * 0xC + rt->table578)).a = 0;
                            (*(LevelSlot *) (id * 0xC + rt->table578)).a = ((LevelWork *) work)->chunks[a].dest / 8;
                            (*(LevelSlot *) (id * 0xC + rt->table578)).b = ((LevelWork *) work)->chunks2[b].dest / 8;
                            f = rec->flags;
                            if (f != 0) {
                                (*(LevelSlot *) (id * 0xC + rt->table578)).c = ((f & 0x7FF) >> 3) | (f & 0xF800);
                            } else {
                                (*(LevelSlot *) (id * 0xC + rt->table578)).c = 0;
                            }
                        }
                    }
                    for (i = 0; i < ((LevelWork *) work)->chunkCount; i++) {
                        rom_dma_read(gLevelModelRom + ((LevelWork *) work)->chunks[i].rom, rt->table57C + ((LevelWork *) work)->chunks[i].dest, ((LevelWork *) work)->chunks[i].size);
                        offset_display_list_image_addresses(rt->table57C + (((LevelWork *) work)->chunks[i].dest / 8) * 8, ((LevelWork *) work)->chunks[i].size / 8, rt->table57C + ((LevelWork *) work)->chunks[i].dest);
                        if ((u8) get_runtime_byte_setting() != 0) {
                            rewrite_display_list_commands(rt->table57C + (((LevelWork *) work)->chunks[i].dest / 8) * 8, ((LevelWork *) work)->chunks[i].size / 8);
                        }
                    }
                    for (i = 0; i < ((LevelWork *) work)->chunk2Count; i++) {
                        rom_dma_read(gLevelTextureRom + ((LevelWork *) work)->chunks2[i].rom, rt->table580 + ((LevelWork *) work)->chunks2[i].dest, ((LevelWork *) work)->chunks2[i].size);
                        func_80085290(rt->table580 + (((LevelWork *) work)->chunks2[i].dest / 8) * 8, ((LevelWork *) work)->chunks2[i].size / 8, rt->table580 + ((LevelWork *) work)->chunks2[i].dest);
                        scale_display_list_vertex_colors(rt->table580 + (((LevelWork *) work)->chunks2[i].dest / 8) * 8, gCurrentFogScale);
                    }
                }
                if (game_mode_is_3_through_6() == 0) {
                    clear_level_input_flags();
                }
                spawn_bank_record_entries(hdr, 0, rt);
                walk_effect_lists();
                if ((gDemoModeFlag != 0) || (gAttractModeFlag != 0)) {
                    spawn_color_effect(0, 0, 0, 0, 0, 0, 0x3C, 2);
                } else if ((level == 1) && (audio_restarts_disabled() == 0)) {
                    get_runtime_rgb_bytes(&red, &green, &blue);
                    spawn_color_effect(0x94, 0x21, 0, red, green, blue, 0x4B0, 0);
                }
                osGetTime();
                return needed;
            }
        }
    }
}
