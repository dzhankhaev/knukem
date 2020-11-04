#include "engine.h"
#include "utilits.h"

void		render_ceil_and_floor(t_engine *engine)
{
	t_temp	*a;

	a = &engine->rend_wall;
	a->oy[0] = y_for_x(a->wall[0], a->x);
	a->oy[1] = y_for_x(a->wall[1], a->x);
	a->y[0] = iclamp(y_for_x(a->wall[0], a->x),
				  engine->tline[a->x], engine->bline[a->x]);		//линия потолка тек
	a->y[1] = iclamp(y_for_x(a->wall[1], a->x),
				  engine->tline[a->x], engine->bline[a->x]);		//линия пола тек
	render_vline(engine->screen, (t_line){a->x, a->x,
				engine->tline[a->x], a->y[0], a->wall[0].color});	//потолок
	render_vline(engine->screen, (t_line){a->x, a->x,
				a->y[1], engine->bline[a->x], a->wall[1].color});	//пол
}

Uint32		get_pixel_color(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)(surface->pixels + y * surface->pitch
				  + (x * surface->format->BytesPerPixel));
	rgb = p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void			render_vline1(t_engine *engine, t_line p, int txx, int txy)
{
	Uint32	*temp;
	t_temp	*a;

	temp = (Uint32 *)engine->screen->pixels;
	a = &engine->rend_wall;
	p.y0 = iclamp(p.y0, 0, H - 1);
	p.y1 = iclamp(p.y1, 0, H - 1);
	while (p.y0 < p.y1)
	{
		txy = 0 + (p.y0 - 1 - a->oy[0]) * (engine->img[0].tx->h - 0) / ((a->oy[1] - a->oy[0]) == 0 ? 1 : (a->oy[1] - a->oy[0]));
		temp[(p.y0 * W) + p.x0] = get_pixel_color(engine->img[0].tx, txx, txy);
		p.y0++;
	}
}


void		render_edge(t_engine *engine, int neighbor, Uint32 z)
{
	t_temp	*a;

	a = &engine->rend_wall;
	if (neighbor != -1)
	{
		a->y[2] = iclamp(y_for_x(a->wall[2], a->x),
						 engine->tline[a->x], engine->bline[a->x]);		//линия потолка соседа
		a->y[3] = iclamp(y_for_x(a->wall[3], a->x),
						 engine->tline[a->x], engine->bline[a->x]);		//линия пола соседа
		//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
		render_vline(engine->screen, (t_line){a->x, a->x, a->y[0],
		imin(a->y[2], a->y[1]), get_shadow(z, a->wall[2].color)}); //	верхняя линия раздела
		//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
		render_vline(engine->screen, (t_line){a->x, a->x,
		imax(a->y[3], a->y[0]), a->y[1], get_shadow(z, a->wall[3].color)}); //	нижняя линия раздела
		engine->tline[a->x] = iclamp(imax(a->y[0],
		a->y[2]), engine->tline[a->x], H - 1);
		engine->bline[a->x] = iclamp(imin(a->y[1],
		a->y[3]), 0, engine->bline[a->x]);
	}
	else
	{
		render_vline1(engine,
					  (t_line){a->x, a->x, a->y[0], a->y[1], engine->wall.color},
					  a->txx,
					  1);
	}
}

