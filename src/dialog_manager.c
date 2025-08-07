// dialog_manager.c
#include "dialog_manager.h"
#include <tice.h>
#include <graphx.h>
#include "gfx/gfx.h"
#include <keypadc.h>
#include <stdbool.h>
#include <string.h>

enum emotion emotion = SMILE; // Define global emotion variable
static bool active = false;
static int currentPage = 0;
static int totalPages = 0;
static const char **pages = NULL;
static bool last2nd = false;
static uint16_t delayCounter = 0;
static uint16_t pageAdvanceCounter = 0;
static const uint16_t DIALOG_DELAY_FRAMES = 20;
static const uint16_t PAGE_ADVANCE_DELAY = 10;
static uint16_t charIndex = 0;
static uint16_t charDelayCounter = 0;
static const uint16_t CHAR_DELAY_FRAMES = 1;

void dialog_init(void) {
    active = false;
    currentPage = 0;
    totalPages = 0;
    pages = NULL;
    last2nd = false;
    delayCounter = 0;
    pageAdvanceCounter = 0;
    charIndex = 0;
    charDelayCounter = 0;
    emotion = SMILE;
}

bool dialog_can_start(void) {
    return !active && delayCounter == 0;
}

void dialog_start(const char **dialogPages, int numPages) {
    if (!dialog_can_start()) return;
    
    pages = dialogPages;
    totalPages = numPages;
    currentPage = 0;
    active = true;
    last2nd = true;
    pageAdvanceCounter = PAGE_ADVANCE_DELAY;
    charIndex = 0;
    charDelayCounter = 0;
    emotion = SMILE; // Reset emotion
}

bool dialog_update(bool now2nd) {
    if (!active && delayCounter > 0) {
        delayCounter--;
        last2nd = now2nd;
        return false;
    }

    if (!active) {
        last2nd = now2nd;
        return false;
    }

    if (pageAdvanceCounter > 0) {
        pageAdvanceCounter--;
        last2nd = now2nd;
        return true;
    }

    // Update typewriter effect
    if (charIndex < strlen(pages[currentPage])) {
        charDelayCounter++;
        if (charDelayCounter >= CHAR_DELAY_FRAMES) {
            charIndex++;
            charDelayCounter = 0;
        }
    }

    // Parse current page for emotion tags
    if (pages && currentPage < totalPages) {
        const char *text = pages[currentPage];
        for (const char *p = text; *p && p - text < (int)charIndex; p++) {
            if (strncmp(p, ":sad", 4) == 0) {
                emotion = SAD;
                p += 3;
            } else if (strncmp(p, ":happy", 6) == 0) {
                emotion = SMILE;
                p += 5;
            }
        }
    }

    if (now2nd && !last2nd) {
        if (charIndex < strlen(pages[currentPage])) {
            charIndex = strlen(pages[currentPage]); // Skip to end of page
        } else {
            currentPage++;
            if (currentPage >= totalPages) {
                active = false;
                delayCounter = DIALOG_DELAY_FRAMES;
                emotion = SMILE; // Reset emotion
            } else {
                pageAdvanceCounter = PAGE_ADVANCE_DELAY;
                charIndex = 0;
                charDelayCounter = 0;
                emotion = SMILE; // Reset emotion for new page
            }
        }
    }

    last2nd = now2nd;
    return active;
}

void dialog_draw(void) {
    if (!active || currentPage >= totalPages || !pages) return;


    gfx_SetTextFGColor(1);
    gfx_TransparentSprite(dialogue, 30, 150);
    gfx_SetTextXY(40, 165);




    const char *text = pages[currentPage];
    int lineHeight = 10;
    int y = 165;
    int currentChar = 0;

    for (const char *p = text; *p && currentChar < charIndex; p++, currentChar++) {
        if (*p == '\n') {
            y += lineHeight;
            gfx_SetTextXY(40, y);
        } else if (strncmp(p, ":sad", 4) == 0) {
            p += 3;
        } else if (strncmp(p, ":happy", 6) == 0) {
            p += 5; 
        } else {
            gfx_PrintChar(*p);
        }
    }
}

bool dialog_is_active(void) {
    return active;
}

bool dialog_is_in_delay(void) {
    return delayCounter > 0;
}