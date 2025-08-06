#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <ti/getcsc.h>
#include "gfx/gfx.h"

void dialog(const char *text) {
    int startX = 40;
    int startY = 165;
    int lineHeight = 10; // thank you chatgpt

    gfx_TransparentSprite(dialogue, 30, 150);

    gfx_SetTextXY(startX, startY);

    for (const char *p = text; *p; p++) {
        if (*p == '\n') {
            // Move to next line
            startY += lineHeight;
            gfx_SetTextXY(startX, startY);
        } else {
            // Print the character
            gfx_PrintChar(*p);
        }
    }
}

int main(void) {
    int x = 50;
    int y = 50;
    int speed;


    
    gfx_Begin();
    gfx_SetDrawBuffer();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    gfx_FillScreen(10);

    while (!kb_IsDown(kb_KeyClear)) {


        kb_Scan();

        if (kb_IsDown(kb_KeyAlpha)) {
            speed = 4;
        } else {
            speed = 1;
        }

        if (kb_IsDown(kb_KeyLeft)) x -= speed;
        if (kb_IsDown(kb_KeyRight)) x += speed;
        if (kb_IsDown(kb_KeyUp))   y -= speed;
        if (kb_IsDown(kb_KeyDown)) y  += speed;
        gfx_SetTextFGColor(1);
        gfx_FillScreen(10); 
        gfx_TransparentSprite(spamton, x, y);
        dialog("IS THAT SERIOUSLY [ALL THERE IS]? \n YES.");
        gfx_SetTextXY(10, 10);  
        gfx_PrintString("DELTIRUNE V0.01");
        gfx_SwapDraw(); 




    }
\

    gfx_End();         
    return 0;


}
