extern void refresh_audio_output_impl(void) __asm__("func_80079D58");
void refresh_audio_output(void) __asm__("func_80079BD4");
void refresh_audio_output(void) { refresh_audio_output_impl(); }
