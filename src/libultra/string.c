#include "types.h"

void* memcpy(void* destination, const void* source, u32 length) {
    u8* destination_bytes = destination;
    const u8* source_bytes = source;

    while (length != 0) {
        *destination_bytes++ = *source_bytes++;
        length--;
    }

    return destination;
}

u32 strlen(const char* string) {
    const char* end = string;

    while (*end != '\0') {
        end++;
    }

    return end - string;
}

char* strchr(const char* string, s32 character) {
    u8 target = character;

    while (*string != target) {
        if (*string == '\0') {
            return 0;
        }
        string++;
    }

    return (char*)string;
}
