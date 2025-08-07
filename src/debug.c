#include "debug.h"
#include <graphx.h>
#include <time.h>   
#include <stdio.h>

static uint32_t lastTime;
static uint32_t frameCount;
static uint32_t fps;

void fps_counter_init(void) {
    lastTime = clock();
    frameCount = 0;
    fps = 0;
}

void fps_counter_update(void) {
    frameCount++;
    uint32_t now = clock();  // ⏰ Replaces timer_GetTicks()

    if (now - lastTime >= 32768) {  // 1 second = 32768 clock ticks
        fps = frameCount;
        frameCount = 0;
        lastTime = now;
    }
}

void fps_counter_draw(void) {
    char buffer[16];
    sprintf(buffer, "%lu FPS", (unsigned long)fps);
    gfx_SetTextFGColor(1);
    gfx_SetTextXY(250, 90);
    gfx_PrintString(buffer);
}

uint32_t fps_counter_get_fps(void) {
    return fps;
}
