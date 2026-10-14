#include "types.h"
typedef struct ActionContext { u8 pad00[0xC]; void *member; } ActionContext;
extern void process_member(void *member) __asm__("func_8009D4DC");
void process_context_member(ActionContext *context) __asm__("func_8009EDAC");
void process_context_member(ActionContext *context) { process_member(context->member); }
