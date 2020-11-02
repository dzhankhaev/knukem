#include "engine.h"

void			render_vline(SDL_Surface *screen, t_line p)
{
	Uint32	*temp;

	temp = (Uint32 *)screen->pixels;
	p.y0 = p.y0 < 0 ? 0 : p.y0;
	p.y0 = p.y0 > H - 1 ? H - 1 : p.y0;
	p.y1 = p.y1 > H - 1 ? H - 1 : p.y1;
	p.y1 = p.y1 < 0 ? 0 : p.y1;
	while (p.y0 < p.y1)
	{
		temp[(p.y0 * W) + p.x0] = p.color;
		p.y0++;
	}
}