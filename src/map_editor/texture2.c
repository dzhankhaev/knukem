#include "editor.h"

Uint32	get_pixel_color1(SDL_Surface *surface, const int x,\
									const int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x
			* surface->format->BytesPerPixel;
	rgb = p[3] << 24 | p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void    draw_texture(SDL_Surface *screen, SDL_Rect area, SDL_Surface *txt)
{
    float x;
    float y;
    Uint32 col;
	float kx, ky;
	
	kx = (float)txt->w / area.w;
	ky = (float)txt->h / area.h;
	
    y = 0;
    while(y < area.h)
    {
        x = 0;
        while(x < area.w)
        {
            col = get_pixel_color1(txt,kx*x, ky*y);
			if(col >> 24 != 0 && col ^ 0xFF00FFFF)
				put_pxl(screen, (SDL_Color){col >> 16, col >> 8, col, 255}, area.x + x, area.y + y);
			x++;
        }
		y++;
    }
}