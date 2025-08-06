#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <ti/getcsc.h>
#include "gfx/gfx.h"
#include "dialog_manager.h"

const char *spamtonDialog[] = {
    "HELLO AGAIN OLD FRIEND.\n NICE TO SEE YOU AGAIN.",
    "ARE YOU FEELING OKAY?\nYOU KNOW YOU CAN ALWAYS\nTURN OFF THE GAME.",
    "BUT WE BOTH KNOW...",
    ".",
    ".",
    "THAT YOU'RE STILL TRAPPED\n INSIDE OF YOUR OWN WALLS.",
    "AREN'T YOU? ;)"
};
const char *NPC1Dialog[] = {
    "IS THAT ALL THERE IS?",
    "I FEEL EMPTY."
};
int main(void) {
    int x = 50, y = 50;
    int speed;
    const int playerW = 16;
    const int playerH = 16;
    const int spamtonX = 10;
    const int spamtonY = 10;
    const int NPC1X = 60;
    const int NPC1Y = 60;

    dialog_init();

    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
        bool now2nd = kb_IsDown(kb_Key2nd);

        if (!dialog_is_active() && !dialog_is_in_delay()) {
            
            speed = kb_IsDown(kb_KeyAlpha) ? 4 : 1;
            if (kb_IsDown(kb_KeyLeft))  x -= speed;
            if (kb_IsDown(kb_KeyRight)) x += speed;
            if (kb_IsDown(kb_KeyUp))    y -= speed;
            if (kb_IsDown(kb_KeyDown))  y += speed;

           
            bool touchingNPC1 =
                x < (NPC1X + spamton_width) &&
                (x + playerW) > NPC1X &&
                y < (NPC1Y + spamton_height) &&
                (y + playerH) > NPC1Y;

            if (touchingNPC1 && now2nd) {
                dialog_start(NPC1Dialog, 2);
            }

            bool touchingSpamton =
                x < (spamtonX + spamton_width) &&
                (x + playerW) > spamtonX &&
                y < (spamtonY + spamton_height) &&
                (y + playerH) > spamtonY;

            if (touchingSpamton && now2nd) {
                dialog_start(spamtonDialog, 7);
            }
        } else {
            dialog_update(now2nd);
        }

        gfx_FillScreen(10);
        gfx_TransparentSprite(spamton, x, y);
        gfx_TransparentSprite(spamton, spamtonX, spamtonY);
        gfx_TransparentSprite(placeholder, NPC1X, NPC1Y);


        if (dialog_is_active()) {
            dialog_draw();
        }
        gfx_SetTextXY(10, 10);
        gfx_SetTextFGColor(1);
        gfx_PrintString("DELTIRUNE V0.02 -- MADE BY AIDEN");
        

        gfx_SwapDraw();
    }

    gfx_End();
    return 0;
}