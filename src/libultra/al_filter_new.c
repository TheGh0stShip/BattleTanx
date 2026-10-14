#include "types.h"

typedef struct AudioFilter {
    void* source;
    void* handler;
    void* set_param;
    s16 input;
    s16 output;
    s32 type;
} AudioFilter;

void alFilterNew(AudioFilter* filter, void* handler, void* set_param, s32 type) {
    filter->source = 0;
    filter->handler = handler;
    filter->set_param = set_param;
    filter->input = 0;
    filter->output = 0;
    filter->type = type;
}
