#include "types.h"

typedef struct ALSynthDriver {
    void* head;
} ALSynthDriver;

void alSynDelete_80110750(ALSynthDriver* driver) {
    driver->head = 0;
}
