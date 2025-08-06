#ifndef PLAYER_H
#define PLAYER_H

#include <tice.h>
#include <graphx.h>
#include "gfx/gfx.h"

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 20

typedef struct {
    int x, y;              // Player position
    uint8_t animFrame;     // 0 for first frame, 1 for second frame
    uint32_t lastAnimTime; // Time of last animation frame change
    bool isMovingLeft;     // Moving left
    bool isMovingRight;    // Moving right
    bool isMovingUp;       // Moving up
    bool isMovingDown;     // Moving down
} Player;

void player_init(Player *player, int startX, int startY);
void player_update(Player *player, bool isAlphaPressed, bool isLeftPressed, bool isRightPressed, bool isUpPressed, bool isDownPressed);
void player_draw(const Player *player);

#endif