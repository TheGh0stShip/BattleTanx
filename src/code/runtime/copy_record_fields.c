#include "types.h"

typedef struct RecordSource {
    u32 first;
    u32 second;
    u8 pad08[4];
    s16 third;
} RecordSource;

typedef struct RecordDestination {
    u8 pad00[8];
    u32 first;
    u32 second;
    u8 pad10[0xA];
    s16 third;
} RecordDestination;

void func_8011954C(RecordDestination *destination, RecordSource *source)
{
    destination->first = source->first;
    destination->third = source->third;
    destination->second = source->second;
}
