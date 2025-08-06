#include "player.h"
#include <time.h>

#define ANIM_DELAY 250 

void player_init(Player *player, int startX, int startY) {
    player->x = startX;
    player->y = startY;
    player->animFrame = 0;
    player->lastAnimTime = 0;
    player->isMovingLeft = false;
    player->isMovingRight = false;
    player->isMovingUp = false;
    player->isMovingDown = false;
}

void player_update(Player *player, bool isAlphaPressed, bool isLeftPressed, bool isRightPressed, bool isUpPressed, bool isDownPressed) {
    int speed = isAlphaPressed ? 2 : 1;


    player->isMovingLeft = false;
    player->isMovingRight = false;
    player->isMovingUp = false;
    player->isMovingDown = false;

    if (isLeftPressed) {
        player->x -= speed;
        player->isMovingLeft = true;
    }
    if (isRightPressed) {
        player->x += speed;
        player->isMovingRight = true;
    }
    if (isUpPressed) {
        player->y -= speed;
        player->isMovingUp = true;
    }
    if (isDownPressed) {
        player->y += speed;
        player->isMovingDown = true;
    }


    if (player->isMovingLeft || player->isMovingRight || player->isMovingUp || player->isMovingDown) {
        uint32_t currentTime = clock() / (CLOCKS_PER_SEC / 1000);
        if (currentTime - player->lastAnimTime >= ANIM_DELAY) {
            player->animFrame = !player->animFrame;
            player->lastAnimTime = currentTime;
        }
    } else {
        player->animFrame = 0; 
    }
}

void player_draw(const Player *player) {

    if (player->isMovingLeft) {
        if (player->animFrame == 0) {
            gfx_TransparentSprite(kriswalk_left1, player->x, player->y);
        } else {
            gfx_TransparentSprite(kriswalk_left2, player->x, player->y);
        }
    } else if (player->isMovingRight) {
        gfx_sprite_t *flippedSprite = gfx_MallocSprite(kriswalk_left1_width, kriswalk_left1_height);
        if (flippedSprite) {
            if (player->animFrame == 0) {
                gfx_FlipSpriteY(kriswalk_left1, flippedSprite);
                gfx_TransparentSprite(flippedSprite, player->x, player->y);
            } else {
                gfx_FlipSpriteY(kriswalk_left2, flippedSprite);
                gfx_TransparentSprite(flippedSprite, player->x, player->y);
            }
            free(flippedSprite);
        }
    } else if (player->isMovingUp) {
        if (player->animFrame == 0) {
            gfx_TransparentSprite(kriswalk_up1, player->x, player->y);
        } else {
            gfx_TransparentSprite(kriswalk_up2, player->x, player->y);
        }
    } else if (player->isMovingDown) {
        if (player->animFrame == 0) {
            gfx_TransparentSprite(kriswalk_down1, player->x, player->y);
        } else {
            gfx_TransparentSprite(kriswalk_down2, player->x, player->y);
        }
    } else {

        gfx_TransparentSprite(kriswalk_down1, player->x, player->y);
    }
}