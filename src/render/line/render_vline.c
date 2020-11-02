#include "engine.h"

void			render_vline(SDL_Surface *screen, t_line p)
{
	Uint32	*temp;

	temp = (Uint32 *)screen->pixels;
	while (p.y0 < p.y1)
	{
		temp[(p.y0 * W) + p.x0] = p.color;
		p.y0++;
	}
}