#include "types.h"

typedef struct TriadEntry {
    u16 value00;
    u16 value02;
} TriadEntry;

typedef struct TriadRecordTable {
    u8 pad00[0x10];
    TriadEntry *triads;
} TriadRecordTable;

extern TriadRecordTable *gObjectRecordTable __asm__("D_80135834");

void get_triad_entry_and_next(u16 index, u16 *current, u16 *next) __asm__("func_800E1818");

void get_triad_entry_and_next(u16 index, u16 *current, u16 *next) {
    u16 corner = index % 3;
    u16 nextCorner = (corner + 1) % 3;

    *current = gObjectRecordTable->triads[index].value00;
    *next = gObjectRecordTable->triads[(u16)(nextCorner + (index - corner))].value00;
}
