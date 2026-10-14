#include "types.h"

typedef struct BitstreamHeader {
    u8 *data;
    u16 value4;
    u16 value6;
    u16 value8;
    u16 valueA;
    u16 limit;
    u16 pad0E;
    u8 payload[1];
} BitstreamHeader;

BitstreamHeader *initialize_bitstream_header(BitstreamHeader *header) __asm__("func_800DDCA4");

BitstreamHeader *initialize_bitstream_header(BitstreamHeader *header)
{
    header->data = header->payload;
    header->value4 = 0;
    header->value6 = 0;
    header->value8 = 0;
    header->valueA = 0;
    header->limit = 0xF8;
    return header;
}
