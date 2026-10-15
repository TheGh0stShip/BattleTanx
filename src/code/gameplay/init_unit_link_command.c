#include "types.h"

typedef struct LinkedUnit LinkedUnit;

typedef struct UnitLinkCommand {
    s32 kind;
    s32 value04;
    u8 pad08[0x8];
    s8 sourceId;
    s8 value11;
    u8 pad12[0x2];
    LinkedUnit *target;
} UnitLinkCommand;

extern LinkedUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void process_unit_link_command(UnitLinkCommand *command) __asm__("func_800E360C");
extern void update_linked_unit(LinkedUnit *unit) __asm__("func_800E5F30");

void init_unit_link_command(UnitLinkCommand *command, s16 sourceId, s16 targetId)
    __asm__("func_800E36FC");

void init_unit_link_command(UnitLinkCommand *command, s16 sourceId, s16 targetId)
{
    LinkedUnit *source;

    source = get_unit(sourceId);
    command->target = get_unit(targetId);
    command->sourceId = sourceId;
    command->value11 = 0;
    command->value04 = 0;
    command->kind = 8;
    process_unit_link_command(command);
    update_linked_unit(source);
}
