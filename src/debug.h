// debug_h
#ifndef debug_h
#define debug_h

#include <stdint.h>

void fps_counter_init(void);
void fps_counter_update(void);
void fps_counter_draw(void);
uint32_t fps_counter_get_fps(void);

#endif
