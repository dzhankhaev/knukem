#include "engine.h"
#include "utilits.h"

void			render_hline1(t_engine *engine, int y, int xbegin, int xend, int txno)
{
	Uint32 *temp;
	t_temp2 *a;
	int x;

	a = &engine->rend_plane;
	x = xbegin;
	temp = (Uint32 *) engine->screen->pixels;
	a->mapx = (engine->player.where.z - engine->sectors[engine->present->sectorno].floor) / (((float)(y << 1) / H - 1) - engine->player.vangle);
	a->cosx = a->mapx * a->pcos;
	a->sinx = -a->mapx * a->psin;
	while (x < xend)
	{
		a->mapy = a->mapx * (((float)x - (W >> 1)) / (W >> 1));
		a->txy = (int)(((a->cosx + a->mapy * a->psin) + engine->player.where.x)
					   * 256) % engine->img[txno].tx->h;
		a->txx = (int)(((a->sinx + a->mapy * a->pcos) + engine->player.where.y)
					   * 256) % engine->img[txno].tx->w;
		temp[(y * W) + x] = get_pixel_color(engine->img[txno].tx,
											a->txx, a->txy);
		x++;
	}
}