#include "types.h"

typedef struct ALSynthDriver {
    void* head;
} ALSynthDriver;

void alSynDelete(ALSynthDriver* driver) {
    driver->head = 0;
}
