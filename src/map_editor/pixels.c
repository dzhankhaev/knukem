#include "editor.h"

void       put_pxl(t_sdl *sdl, SDL_Color col, int x, int y)
{
    Uint32 *temp;
    int pos;
    Uint32 color;

    temp = (Uint32*)sdl->screen->pixels;
    pos = y * WIDTH + x;
    color = col.a << 24 | col.r << 16 | col.g << 8 | col.b;
    if(x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
        // if(pos < WIDTH * HEIGHT && pos >= 0)
            temp[pos] = color;
}