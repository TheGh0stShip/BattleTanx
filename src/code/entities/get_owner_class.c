#include "types.h"
typedef struct OwnerRef { u8 pad00[0x4]; u8 ownerId; } OwnerRef;
typedef struct EntityRecord { u8 pad000[0x1AE]; u8 classId; } EntityRecord;
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
u8 get_owner_class(OwnerRef *ref) __asm__("func_8009FBE4");
u8 get_owner_class(OwnerRef *ref) { return get_entity_record(ref->ownerId)->classId; }
