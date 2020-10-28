#include "engine.h"

void			render_vline(t_line p, SDL_Surface *screen)
{
	int	*temp;

	temp = (int *)screen->pixels;
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