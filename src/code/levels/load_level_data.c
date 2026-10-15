#include "types.h"

typedef struct LevelDataHeader {
    u8 *end;
    u8 *section04;
    u8 pad08[4];
    u8 *section0C;
    u8 *section10;
    u8 *section14;
    u8 *section18;
    u8 *section1C;
} LevelDataHeader;

typedef struct LevelDataRomEntry {
    u32 romStart;
    u32 romEnd;
    u8 pad08[8];
} LevelDataRomEntry;

typedef struct WaypointQuery {
    s32 value00;
    s32 value04;
} WaypointQuery;

extern void rom_dma_read(u32 romAddress, void *destination, s32 size) __asm__("func_80077930");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern void clear_runtime_workspace(void) __asm__("func_800DEC04");
extern void select_level_waypoint_set(u16 index) __asm__("func_800E055C");
extern u16 find_level_waypoint_set(WaypointQuery *query) __asm__("func_800E05A4");
extern void set_runtime_record_value20(s32 value) __asm__("func_800E097C");
extern void ai_unused_callback(void) __asm__("func_800E4814");
extern void level_data_relocated_callback(u8 *a, u8 *b, u8 *c, u8 *d) __asm__("func_800E5198");
extern s32 runtime_slot_is_active(s32 index, s32 a, s32 b, s32 c) __asm__("func_800E51A0");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern LevelDataRomEntry gLevelDataRomTable[] __asm__("D_80125A70");
extern s8 D_80135820;
extern LevelDataHeader *gLevelData __asm__("D_80135834");

void load_level_data(u32 size, u8 *buffer, s32 index) __asm__("func_800DDA08");
void load_level_data(u32 size, u8 *buffer, s32 index) {
    s32 capacity = get_entity_capacity();
    u32 romStart;
    u32 packedSize;
    u8 *packed;
    LevelDataHeader *header;
    u8 *section04;
    u8 *section0C;
    u8 *section10;
    u8 *section14;
    u8 *section18;
    u8 *section1C;
    WaypointQuery query;

    if (runtime_slot_is_active(index, -1, capacity, get_difficulty_level()) == 0) {
        gLevelData = 0;
        return;
    }
    if (size < 0x24) {
        return;
    }
    romStart = gLevelDataRomTable[index].romStart;
    if (romStart == 0) {
        return;
    }
    gLevelData = (LevelDataHeader *)buffer;
    packedSize = (gLevelDataRomTable[index].romEnd - romStart + 8) & ~0xF;
    set_runtime_record_value20(2);
    packed = (u8 *)((u32)(buffer + size - packedSize) & ~0xF);
    rom_dma_read(romStart, packed, packedSize);
    lzari_decode(packedSize, packed, size, buffer);
    header = gLevelData;
    section04 = header->section04;
    section0C = header->section0C;
    section10 = header->section10;
    section14 = header->section14;
    section18 = header->section18;
    section1C = header->section1C;
    D_80135820 = 0;
    header->end = (u8 *)header + size;
    section04 += (u32)header;
    section0C += (u32)header;
    section10 += (u32)header;
    section14 += (u32)header;
    section18 += (u32)header;
    section1C += (u32)header;
    header->section04 = section04;
    header->section0C = section0C;
    header->section10 = section10;
    header->section14 = section14;
    header->section18 = section18;
    header->section1C = section1C;
    level_data_relocated_callback(section04, section0C, section10, section14);
    ai_unused_callback();
    query.value04 = 0;
    query.value00 = 0;
    select_level_waypoint_set(find_level_waypoint_set(&query));
    clear_runtime_workspace();
    set_runtime_record_value20(9);
}
