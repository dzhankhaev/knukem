#include "engine.h"
#include "utilits.h"

//p - столбец, op - столбец до обрезания по краям экрана
void		render_vline(t_engine *engine, t_line p, t_line op, int texture_n)
{
	Uint32	*temp;
	int		txy;
	int		t;
	t_temp	*a;

	temp = (Uint32 *)engine->screen->pixels;
	a = &engine->rend_wall;
	p.y0 = iclamp(p.y0, 0, H - 1);
	p.y1 = iclamp(p.y1, 0, H - 1);
	t = op.y1 - op.y0 == 0 ? 1 : (op.y1 - op.y0);
	while (p.y0 < p.y1)
	{
		txy = (p.y0 - op.y0) * engine->img[texture_n].tx->h / t;
		temp[(p.y0 * W) + p.x0] = get_shadow(a->z,
											 get_pixel_color(engine->img[texture_n].tx, a->txx, txy));
		p.y0++;
	}
}