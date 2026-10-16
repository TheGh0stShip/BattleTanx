#include "types.h"

/* RODATA_VRAM 0x80072DA0 */
/* LDSYM D_010001E0=0x010001E0 */
/* LDSYM D_801260F8=0x801260F8 */
/* LDSYM D_80126128=0x80126128 */
/* LDSYM D_80126140=0x80126140 */
/* LDSYM D_80134E68=0x80134E68 */
/* LDSYM D_80135772=0x80135772 */
/* LDSYM D_803282A8=0x803282A8 */
/* LDSYM D_803283B8=0x803283B8 */
/* LDSYM func_80077B10=0x80077B10 */
/* LDSYM func_80078834=0x80078834 */
/* LDSYM func_8007AAA0=0x8007AAA0 */
/* LDSYM func_8007AAF4=0x8007AAF4 */
/* LDSYM func_8007C6D8=0x8007C6D8 */
/* LDSYM func_8007C770=0x8007C770 */
/* LDSYM func_80081A30=0x80081A30 */
/* LDSYM func_800821C0=0x800821C0 */
/* LDSYM func_80086AE8=0x80086AE8 */
/* LDSYM func_80096FC8=0x80096FC8 */
/* LDSYM func_80097038=0x80097038 */
/* LDSYM func_800A03B8=0x800A03B8 */
/* LDSYM func_800A68C0=0x800A68C0 */
/* LDSYM func_800EA1B0=0x800EA1B0 */
/* LDSYM func_800EC644=0x800EC644 */
/* LDSYM func_800EC6BC=0x800EC6BC */
/* LDSYM func_80110C00=0x80110C00 */
/* LDSYM func_80114970=0x80114970 */
typedef struct SpawnPoint
{
  f32 x;
  f32 z;
  u16 angle;
  u8 pad0A[0x2];
} SpawnPoint;
typedef struct PlayerSetup
{
  u16 index;
  u16 slot;
  SpawnPoint *spawns;
  void *portrait;
  void *banner;
  u8 team;
  u8 local;
  u8 pad12[0x2];
  s32 controller;
  s32 lives;
  u8 respawn;
  u8 red;
  u8 green;
  u8 blue;
  u8 color;
  u8 order;
  u8 pad22[0x2];
  s32 reserve;
  s32 value28;
  u16 bounds[4];
  s32 value34;
} PlayerSetup;
typedef struct TeamEntry
{
  f32 x;
  f32 z;
  s32 limitX;
  s32 limitY;
  s32 limitZ;
  u16 *unitsA;
  u16 *unitsB;
  u8 tint[5];
  u8 pad21[0x3];
} TeamEntry;
typedef struct GameModeInfo
{
  s32 mode;
  u8 pad004[0x18];
  TeamEntry teams[8][4];
} GameModeInfo;
typedef struct GameModeTail
{
  u8 pad000[0x1CC];
  s32 viewMode;
  u8 pad1D0[0x47];
  u8 teamSet;
} GameModeTail;
typedef struct ColorInfo
{
  u8 count;
  u8 pad01[0x3];
  s32 kinds[5];
  u8 record[0x24];
} ColorInfo;
typedef struct MarkerSlot
{
  f32 x;
  f32 z;
  u16 angle;
  u8 pad0A[0x2];
  s32 kind;
  u8 param;
  u8 pad11[0x7];
} MarkerSlot;
typedef struct SpawnSession
{
  u8 pad000[0x370];
  s32 counts[4];
  MarkerSlot slots[4][5];
  u8 slotColor[4];
} SpawnSession;
typedef struct UnitSpawn
{
  u8 primary;
  u8 pad01;
  u16 player;
  f32 x;
  f32 y;
  f32 z;
  u16 angle;
  u8 value12;
  u8 pad13;
  u16 value14;
  u8 selectable;
  u8 pad17;
  s32 kind;
  u16 flags;
  u8 value1E;
  u8 pad1F;
} UnitSpawn;
typedef struct SpawnedUnit
{
  u8 pad000[0x18];
  s32 kind;
  u8 pad01C[0x4E8];
  s32 value504;
} SpawnedUnit;
typedef struct PaletteBlock
{
  s32 data[17];
} PaletteBlock;
typedef struct PlayerRecord
{
  u16 units[5];
  u8 pad0A[0x2];
  s32 controller;
  s32 value10;
  u8 pad14;
  u8 order;
  u16 index;
  s32 value18;
  s32 value1C;
  s16 activeUnit;
  u8 lives;
  u8 value23;
  u8 flag24;
  u8 flag25;
  u8 pad26[0x12];
  u8 reserve;
  u8 pad39;
  s16 bounds3A;
  s16 bounds3C;
  s16 bounds3E;
  s16 bounds40;
  s16 bounds42;
  s16 value44;
  u8 pad46[0x2];
  u8 camera[0xA4];
  s32 valueEC;
  u8 valueF0;
  u8 padF1[0x3];
  void *banner;
  void *portrait;
  u8 viewFC[0x4];
  u8 view100[0x44];
  f32 spawnZ;
  f32 spawnX;
  s32 value14C;
  u8 value150[0x40];
  f32 home[2];
  s32 value198;
  s32 value19C;
  s32 value1A0;
  u8 value1A4;
  u8 value1A5;
  u8 local;
  u8 pad1A7;
  s16 value1A8;
  s16 value1AA;
  s16 value1AC;
  u8 team;
  u8 value1AF;
  u8 pad1B0[0xC];
  u8 red;
  u8 green;
  u8 blue;
  u8 color;
  PaletteBlock palette;
  u8 paletteIndex;
  u8 pad205[0x3];
  s32 reserveCount;
  s32 slotColor;
  s32 value210;
  s32 value214;
  s32 value218;
  s32 value21C;
  u8 pad220[0x40];
  s32 kills[40];
  u8 pad300[0x4];
  s32 value304;
  u8 value308;
  u8 value309;
  u8 pad30A[0x2];
  u32 difficulty;
  f32 limit[3];
  f32 tint[5];
  f32 homeScaled[2];
  u16 unitsA[4];
  u16 unitsB[4];
} PlayerRecord;
extern u8 D_010001E0[];
extern UnitSpawn D_801260F8;
extern s32 D_80126128;
extern s32 D_80126140[];
extern u8 D_80134E68;
extern u8 D_80135772;
extern PaletteBlock D_803282A8[];
extern u8 D_803283B8[];
extern SpawnSession *func_800821C0(void);
extern GameModeInfo *get_game_mode(void) __asm__("func_8007AAF4");
extern void bzero(void *ptr, s32 size) __asm__("func_80110C00");
extern s32 func_8007C6D8(void);
extern ColorInfo *func_800A68C0(s32 controller);
extern void func_8007C770(u8 *record, TeamEntry *entry);
extern s32 func_800EC644(void);
extern void func_800EA1B0(u8 *state);
extern s16 func_800EC6BC(u16 player, u16 index);
extern void func_80097038(s16 unit, UnitSpawn *spawn);
extern s32 func_80096FC8(PlayerRecord *player, SpawnSession *session);
extern u8 func_80081A30(void);
extern s32 func_80086AE8(void);
extern void func_80114970(u8 *view, u8 *viewFC, f32 fov, f32 scale, f32 nearPlane, f32 farPlane, f32 aspect);
extern SpawnedUnit *func_800A03B8(s16 unit);
extern s32 func_80078834(f32 x, f32 z, u16 angle, s32 mode, s32 owner);
extern void func_80077B10(u8 *camera, s32 arg1, s32 arg2, s32 mode);
extern s32 get_view_count(void) __asm__("func_8007AAA0");
void initialize_player_record(PlayerRecord *arg0, PlayerSetup *setup) __asm__("func_800A31C0");

void initialize_player_record(PlayerRecord *arg0, PlayerSetup *setup)
{
  register PlayerRecord *p __asm__("$17") = arg0;
  SpawnSession *session;
  GameModeInfo *gm;
  TeamEntry *entry;
  ColorInfo *info;
  register SpawnedUnit *unit __asm__("$16");
  s32 *table;
  f32 scale;
  f32 limit;
  register u16 i __asm__("$18");
  u16 k;
  int best;
  s32 index;
  u16 unitId;
  u32 mode;
  session = func_800821C0();
  gm = get_game_mode();
  entry = &gm->teams[((GameModeTail *) gm)->teamSet][setup->index];
  bzero(p, sizeof(PlayerRecord));
  for (i = 0, unitId = setup->slot; i < 5; i++, unitId++)
  {
    p->units[i] = unitId;
  }

  p->activeUnit = setup->slot;
  p->banner = setup->banner;
  p->portrait = setup->portrait;
  p->index = setup->index;
  p->red = setup->red;
  p->green = setup->green;
  p->blue = setup->blue;
  p->color = setup->color;
  p->value23 = 0;
  p->order = setup->order;
  p->value18 = 1;
  p->value1C = 1;
  p->value44 = 1;
  p->bounds3A = (p->bounds3C = setup->bounds[0]);
  if ((((D_80135772 != 0) && (p->bounds3A == 0)) && (func_8007C6D8() != 0)) && (p->index == 0))
  {
    p->bounds3C = 1;
    p->bounds3A = 1;
  }
  p->bounds3E = setup->bounds[1];
  p->bounds40 = setup->bounds[2];
  p->bounds42 = setup->bounds[3];
  info = func_800A68C0(p->controller = setup->controller);
  func_8007C770(info->record, entry);
  p->value10 = 1;
  if (func_800EC644() != 0)
  {
    p->spawnX = 0.0f;
    p->spawnZ = 0.0f;
  }
  else
  {
    p->spawnX = setup->spawns->x;
    p->spawnZ = setup->spawns->z;
  }
  p->value14C = 1;
  func_800EA1B0(p->value150);
  for (k = 0; k < 2; k++)
  {
    p->home[k] = 0.0f;
  }

  p->home[0] = entry->x;
  p->home[1] = entry->z;
  p->homeScaled[0] = entry->x * 100.0f;
  p->homeScaled[1] = entry->z * 100.0f;
  p->value198 = 0;
  p->value19C = 0;
  p->value1A0 = 0;
  p->value1A4 = 1;
  p->value1A5 = 1;
  p->value1A8 = 0xFF;
  p->value1AA = 0xFF;
  p->value1AC = 0;
  p->local = setup->local;
  p->difficulty = setup->value34;
  p->tint[0] = entry->tint[0];
  p->tint[1] = entry->tint[1];
  p->tint[2] = entry->tint[2];
  p->tint[3] = entry->tint[3];
  p->tint[4] = entry->tint[4];
  for (i = 0; i < 4; i++)
  {
    p->unitsA[i] = entry->unitsA[i];
    p->unitsB[i] = entry->unitsB[i];
  }

  if (p->local != 0)
  {
    p->limit[0] = entry->limitX;
    p->limit[1] = entry->limitY;
    p->limit[2] = entry->limitZ;
  }
  else
  {
    switch (p->difficulty)
    {
      case 0:
        limit = 80.0f;
        break;

      case 2:
        limit = 120.0f;
        break;

      case 1:

      default:
        limit = 100.0f;
        break;

    }

    p->limit[0] = limit;
    p->limit[1] = limit;
    p->limit[2] = limit;
  }
  p->team = setup->team;
  p->value1AF = 0;
  p->reserveCount = setup->reserve;
  p->value210 = setup->value28;
  p->value214 = setup->value28;
  p->slotColor = session->slotColor[p->index];
  p->value218 = 0;
  p->value21C = 0;
  for (i = 0; i < 40; i++)
  {
    p->kills[i] = 0;
  }

  p->lives = 0;
  p->value304 = 30;
  p->flag24 = 0;
  p->flag25 = 0;
  p->reserve = setup->lives;
  if (func_800EC644() != 0)
  {
    for (i = 0; i < setup->lives; i++)
    {
      D_801260F8.primary = i == 0;
      D_801260F8.value12 = 1;
      D_801260F8.player = setup->index;
      D_801260F8.value14 = func_800EC6BC(setup->index, i);
      D_801260F8.selectable = 0;
      D_801260F8.kind = 0;
      D_801260F8.value1E = 0;
      func_80097038(p->units[i], &D_801260F8);
    }

  }
  else
    if (((mode = get_game_mode()->mode) < 7) && (mode >= 3))
  {
    best = 0;
    if (setup->local == 0)
    {
      for (i = 0; i < session->counts[setup->index]; i++)
      {
        if (session->slots[setup->index][i].kind == 10)
        {
          best = i;
        }
      }

    }
    if (p->local != 0)
    {
      p->reserve = 5;
    }
    else
    {
      p->reserve = session->counts[setup->index];
    }
    for (i = 0; i < session->counts[setup->index]; i++)
    {
      D_801260F8.primary = i == best;
      if (D_801260F8.primary)
      {
        p->activeUnit = p->units[i];
      }
      D_801260F8.player = setup->index;
      D_801260F8.x = session->slots[setup->index][i].x;
      D_801260F8.y = 0.0f;
      D_801260F8.z = session->slots[setup->index][i].z;
      D_801260F8.angle = session->slots[setup->index][i].angle;
      D_801260F8.value12 = 0;
      if (session->slots[setup->index][i].kind < 10)
      {
        D_801260F8.kind = session->slots[setup->index][i].kind;
      }
      else
      {
        D_801260F8.kind = info->kinds[session->slots[setup->index][i].kind - 10];
      }
      D_801260F8.value1E = session->slots[setup->index][i].param;
      D_801260F8.selectable = (setup->local != 0) ? (0) : (i == best);
      if ((setup->local != 0) || (get_game_mode()->mode == 7))
      {
        D_801260F8.flags = 0x40;
      }
      else
      {
        D_801260F8.flags = 0;
      }
      if (p->local == 0)
      {
        if ((D_801260F8.kind == 2) && func_80096FC8(p, session))
        {
          if (p->flag25 == 0)
          {
            p->flag25 = 1;
          }
          else
          {
            D_801260F8.flags |= 0x100;
          }
        }
        else
          if (D_801260F8.selectable)
        {
          p->flag24 = 1;
        }
        else
        {
          D_801260F8.flags |= 0x100;
        }
      }
      func_80097038(p->units[i], &D_801260F8);
    }

  }
  else
  {
    for (i = 0; i < info->count; i++)
    {
      if (get_game_mode()->mode == 7)
      {
        index = i;
      }
      else
      {
        switch (i)
        {
          case 0:
            index = 0;
            break;

          case 1:
            index = info->count - 1;
            break;

          default:
            index = i - 1;
            break;

        }

      }
      if (p->lives < p->reserve)
      {
        D_801260F8.primary = i == 0;
        D_801260F8.player = setup->index;
        D_801260F8.x = setup->spawns[index].x;
        D_801260F8.y = 0.0f;
        D_801260F8.z = setup->spawns[index].z;
        D_801260F8.angle = setup->spawns[index].angle;
        D_801260F8.value12 = 0;
        D_801260F8.kind = (D_80134E68 != 0) ? (0) : (info->kinds[index]);
        D_801260F8.selectable = (setup->local != 0) ? (0) : (i == 0);
        if ((setup->local != 0) || (get_game_mode()->mode == 7))
        {
          D_801260F8.flags = 0x40;
        }
        else
        {
          D_801260F8.flags = 0;
        }
        D_801260F8.value1E = 0;
        func_80097038(p->units[i], &D_801260F8);
      }
      else
        if (setup->local == 0)
      {
        p->bounds3A++;
      }
    }

  }
  if (setup->respawn != 0)
  {
    p->value308 = 1;
    p->value309 = 1;
  }
  if (setup->banner != 0)
  {
    if (setup->banner == D_010001E0)
    {
      scale = 2.19130444526672363281f;
    }
    else
      if ((((GameModeTail *) gm)->viewMode == 2) || ((((GameModeTail *) gm)->viewMode == 3) && (setup->index == 0)))
    {
      scale = 2.66666674613952636719f;
    }
    else
    {
      scale = 1.33333337306976318359f;
    }
    if (func_80081A30())
    {
      func_80114970(p->view100, p->viewFC, 37.0f, scale, 16.0f, (s16) func_80086AE8(), 1.0f);
    }
    else
    {
      func_80114970(p->view100, p->viewFC, 37.0f, scale, 16.0f, 5000.0f, 1.0f);
    }
    unit = func_800A03B8(p->activeUnit);
    if (func_800EC644() != 0)
    {
      func_80077B10(p->camera, D_80126128, func_80078834(0.0f, 0.0f, 0, 1, ((u8 *) (&p->index))[1]), 3);
    }
    else
    {
      table = D_80126140;
      if (get_view_count() >= 2)
      {
        table += 3;
      }
      func_80077B10(p->camera, table[unit->kind], unit->value504, 2);
      p->valueF0 = 1;
      p->valueEC = unit->value504;
    }
  }
  p->palette = D_803282A8[p->order];
  p->paletteIndex = D_803283B8[p->order];
}
