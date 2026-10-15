#include "types.h"

typedef struct SkinPlayer {
    u8 pad000[0x27C];
    s32 groupCount;
    s32 baseGroup;
    u8 pad284[0x58];
    s32 materialBase;
} SkinPlayer;

typedef struct SkinGroup {
    u16 count;
    u16 first;
    u8 pad04[0x10];
} SkinGroup;

typedef struct SkinNode {
    u8 pad00[0x18];
    s16 material;
    u8 pad1A[2];
} SkinNode;

typedef struct SkinMaterial {
    u8 count;
    u8 pad01;
    u16 first;
    u8 pad04[8];
} SkinMaterial;

typedef struct SkinEntry {
    u8 count;
    u8 pad01;
    u16 first;
} SkinEntry;

typedef struct SkinTexture {
    u32 image;
    u8 pad04[0xC];
} SkinTexture;

typedef struct SkinContext {
    SkinPlayer *players;
    SkinGroup *groups;
    SkinNode *nodes;
    SkinMaterial *materials;
    u8 pad10[4];
    SkinEntry *entries;
    SkinTexture *textures;
} SkinContext;

extern s32 func_8007AAA0(void);
extern u8 D_801260A0[];

void swap_player_skin_textures(SkinContext *ctx, s32 player, u32 *slots) __asm__("func_80087D30");

void swap_player_skin_textures(SkinContext *ctx, s32 player, u32 *slots) {
    u32 swap[2][4];
    SkinPlayer *rec;
    SkinGroup *group;
    SkinGroup *groups;
    SkinNode *node;
    SkinMaterial *material;
    SkinEntry *entry;
    SkinTexture *texture;
    s32 n = 0;
    s32 i = 0;
    s32 g;
    s32 idx;
    s32 a;
    s32 b;
    s32 c;

    for (; i < func_8007AAA0(); i++) {
        if (slots[i] >= 9) {
            continue;
        }
        idx = slots[i] + 0x30;
        material = &ctx->materials[ctx->players[player].materialBase + idx];
        entry = &ctx->entries[material->first];
        texture = &ctx->textures[entry->first];
        swap[1][n] = texture->image;
        material = &ctx->materials[ctx->players[player].materialBase + 0x3C];
        entry = &ctx->entries[material->first];
        if (entry->count != 4) {
            return;
        }
        texture = &ctx->textures[entry->first + D_801260A0[i]];
        swap[0][n++] = texture->image;
    }
    if (n == 0) {
        return;
    }
    for (i = 0; i < n; i++) {
    }
    rec = &ctx->players[player];
    for (g = 0; g < rec->groupCount; g++) {
        groups = ctx->groups;
        group = (rec->baseGroup != -1) ? &groups[g + 1] : &groups[g];
        for (a = 0; a < group->count; a++) {
            node = &ctx->nodes[a + group->first];
            material = &ctx->materials[node->material];
            for (b = 0; b < material->count; b++) {
                entry = &ctx->entries[material->first + b];
                for (c = 0; c < entry->count; c++) {
                    texture = &ctx->textures[entry->first + c];
                    for (i = 0; i < n; i++) {
                        if (texture->image == swap[0][i]) {
                            texture->image = swap[1][i];
                        }
                    }
                }
            }
        }
    }
}
