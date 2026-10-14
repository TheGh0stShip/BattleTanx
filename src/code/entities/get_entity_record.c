#include "types.h"
typedef struct EntityRecord { u8 bytes[0x348]; } EntityRecord;
extern EntityRecord D_802DE620[];
EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
EntityRecord *get_entity_record(u16 index) { return &D_802DE620[index]; }
