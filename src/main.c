// src/main.c
#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <ti/getcsc.h>
#include "gfx/gfx.h"
#include "dialog_manager.h"
#include "player.h" 
#include <time.h>

const char *spamtonDialog[] = {
    "HELLO AGAIN OLD FRIEND.\n NICE TO SEE YOU AGAIN.",
    "I SEE YOU'RE ESCAPING REALITY \n AGAIN. TRYING TO FIND \n GOLD INSIDE BRICKS...",
    ":sad ARE YOU FEELING OKAY?\nYOU KNOW YOU CAN ALWAYS\nTURN OFF THE GAME.",
    "BUT WE BOTH KNOW...",
    ".",
    ".",
    "THAT YOU'RE STILL TRAPPED\n INSIDE OF YOUR OWN WALLS.",
    "AREN'T YOU?"
};
const char *NPC1Dialog[] = {
    "IS THAT ALL THERE IS?",
    "I FEEL EMPTY."
};

int main(void) {
    Player player;
    const int spamtonX = 10;
    const int spamtonY = 10;
    const int NPC1X = 60;
    const int NPC1Y = 60;

    dialog_init();
    player_init(&player, 50, 50);

    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
        bool now2nd = kb_IsDown(kb_Key2nd);

        if (!dialog_is_active() && !dialog_is_in_delay()) {

            player_update(&player,
                          kb_IsDown(kb_KeyAlpha),
                          kb_IsDown(kb_KeyLeft),
                          kb_IsDown(kb_KeyRight),
                          kb_IsDown(kb_KeyUp),
                          kb_IsDown(kb_KeyDown));


            bool touchingNPC1 =
                player.x < (NPC1X + PLAYER_WIDTH) &&
                (player.x + PLAYER_WIDTH) > NPC1X &&
                player.y < (NPC1Y + PLAYER_HEIGHT) &&
                (player.y + PLAYER_HEIGHT) > NPC1Y;

            if (touchingNPC1 && now2nd) {
                dialog_start(NPC1Dialog, 2);
            }

            bool touchingSpamton =
                player.x < (spamtonX + PLAYER_WIDTH) &&
                (player.x + PLAYER_WIDTH) > spamtonX &&
                player.y < (spamtonY + PLAYER_HEIGHT) &&
                (player.y + PLAYER_HEIGHT) > spamtonY;

            if (touchingSpamton && now2nd) {
                dialog_start(spamtonDialog, 8);
            }
        } else {
            dialog_update(now2nd);
        }


        gfx_FillScreen(10);
        player_draw(&player);

        if (emotion == SAD) {
            gfx_TransparentSprite(spamtonsad, spamtonX, spamtonY);
        } else if (emotion == SMILE) {
            gfx_TransparentSprite(spamton, spamtonX, spamtonY);
        }


        gfx_TransparentSprite(placeholder, NPC1X, NPC1Y);

        if (dialog_is_active()) {
            dialog_draw();
        }

        gfx_SetTextXY(10, 10);
        gfx_SetTextFGColor(1);
        gfx_PrintString("DELTIRUNE V0.10 -- MADE BY AIDEN");
        gfx_SetTextXY(10, 20);
        gfx_PrintString("TEST SCREEN ONE");

        gfx_SwapDraw();
    }

    gfx_End();
    return 0;
}