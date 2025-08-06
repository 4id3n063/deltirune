#include "dialog_manager.h"
#include <tice.h>
#include <graphx.h>
#include "gfx/gfx.h"
#include <keypadc.h>
#include <stdbool.h>

// Internal state
static bool active = false;
static int currentPage = 0;
static int totalPages = 0;
static const char **pages = NULL;
static bool last2nd = false;
static uint16_t delayCounter = 0;
static uint16_t pageAdvanceCounter = 0; // New counter for page advance delay
static const uint16_t DIALOG_DELAY_FRAMES = 20; // 20 frames (~1/3 second at ~60 FPS)
static const uint16_t PAGE_ADVANCE_DELAY = 10; // 10 frames (~1/6 second at ~60 FPS)

void dialog_init(void) {
    active = false;
    currentPage = 0;
    totalPages = 0;
    pages = NULL;
    last2nd = false;
    delayCounter = 0;
    pageAdvanceCounter = 0;
}

bool dialog_can_start(void) {
    // Check if delay period has passed
    return !active && delayCounter == 0;
}

void dialog_start(const char **dialogPages, int numPages) {
    if (!dialog_can_start()) return;
    
    pages = dialogPages;
    totalPages = numPages;
    currentPage = 0;
    active = true;
    last2nd = true; // Assume key is pressed to avoid immediate advance
    pageAdvanceCounter = PAGE_ADVANCE_DELAY; // Start with delay to prevent instant advance
}

bool dialog_update(bool now2nd) {
    // If in delay period, ignore all inputs and just count down
    if (!active && delayCounter > 0) {
        delayCounter--;
        last2nd = now2nd; // Track key state
        return false;
    }

    if (!active) {
        last2nd = now2nd;
        return false;
    }

    // Handle page advance delay
    if (pageAdvanceCounter > 0) {
        pageAdvanceCounter--;
        last2nd = now2nd; // Track key state
        return true;
    }

    // Advance page or close dialog on 2nd press (edge)
    if (now2nd && !last2nd) {
        currentPage++;
        if (currentPage >= totalPages) {
            active = false;
            delayCounter = DIALOG_DELAY_FRAMES; // Start 20-frame delay
        } else {
            pageAdvanceCounter = PAGE_ADVANCE_DELAY; // Reset page advance delay
        }
    }

    last2nd = now2nd;
    return active;
}

void dialog_draw(void) {
    if (!active || currentPage >= totalPages) return;

    gfx_TransparentSprite(dialogue, 30, 150);
    gfx_SetTextXY(40, 165);

    const char *text = pages[currentPage];
    int lineHeight = 10;
    int y = 165;

    for (const char *p = text; *p; p++) {
        if (*p == '\n') {
            y += lineHeight;
            gfx_SetTextXY(40, y);
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