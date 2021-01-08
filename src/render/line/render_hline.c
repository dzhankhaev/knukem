#include "engine.h"
#include "utilits.h"

void			render_hline(t_engine *engine, int y, int xbegin, int xend)
{
	Uint32 *temp;
	t_temp2 *a;
	int x;

	a = &engine->rend_plane;
	x = xbegin;
	temp = (Uint32 *)engine->screen->pixels;
	a->mapx = a->z / (((float)(y << 1) / H - 1) - engine->player.vangle);
	a->cosx = a->mapx * a->pcos;
	a->sinx = -a->mapx * a->psin;
	while (x < xend)
	{
		a->mapy = a->mapx * (((float)x - (W >> 1)) / (W >> 1));
		a->txy = (int)(((a->cosx + a->mapy * a->psin) + engine->player.where.x)
					   * 256) % a->tx->h;
		a->txx = (int)(((a->sinx + a->mapy * a->pcos) + engine->player.where.y)
					   * 256) % a->tx->w;
		temp[(y * W) + x] = get_pixel_color(a->tx,
											a->txx, a->txy);
		x++;
	}
}