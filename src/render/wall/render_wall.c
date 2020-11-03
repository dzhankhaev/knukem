#include "utilits.h"

void			render_vline1(t_engine *engine, t_line p, int dx, int dy);

static void		loop(t_engine *engine, int neighbor)
{
	t_temp	*a;

	a = &engine->rend_wall;
	//потребуется для вычисления света. Для других вычислений нужно упорядочить
	a->w = (t_line){a->wall[0].x0, a->wall[0].x1, a->wall[0].y0, a->wall[0].y1};
	to_x_order(a->wall);
	a->l = engine->wall;
	a->x = a->x0;
	while (a->x < a->x1)
	{
//		X координата текстуры с учетом перспективы. ew.x - координата глубины. Остальные х - экранная координата ширины
//		https://en.wikipedia.org/wiki/Texture_mapping#Perspective_correctness
//		формула оптимизирована a = (x-wall[0].x0) / (wall[0].x1-wall[0].x0)
		a->txx = (engine->u0 * ((a->wall[0].x1 - a->x) * a->l.x1)
		+ engine->u1 *((a->x - a->wall[0].x0) * a->l.x0))
		/ ((a->wall[0].x1 - a->x) * a->l.x1 + (a->x - a->wall[0].x0) * a->l.x0);
		render_ceil_and_floor(engine, a->x, a->wall, a->y);
		if (neighbor != -1)
			render_edge(engine, a->x, a->wall, a->y, deep_shading(engine, a->w, a->x));
		else
		{
			render_vline1(engine,
						  (t_line){a->x, a->x, a->y[0], a->y[1], engine->wall.color},
						  a->txx,
						  1);
		}
		a->x++;
	}
}

static void		render_init(t_engine *engine, int sectorno, int neighbor)
{	//0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	//соседи (линии раздела) отображаются нак грани текущего сектора, если они имеют общую грань
	t_temp		*a;

	a = &engine->rend_wall;
	init_ceil_floor(engine, engine->sectors[sectorno], a->wall);
	//стены строго вертикально, потому у 0 и 1 иксы одинаковы
	a->x0 = imax(imin(a->wall[0].x0, a->wall[0].x1), engine->present->x0);			//заполняем в промежутке текущей стены
	a->x1 = imin(imax(a->wall[1].x0, a->wall[1].x1), engine->present->x1);			//иксы у пола и потолка всегда равны
	if (neighbor != -1)
	{
		if ((a->x1 > a->x0) && engine->future + 1 != engine->queue + engine->max_queue &&
			check_repeat(engine, sectorno, neighbor))
			*(engine->future++) = (t_queue){neighbor, a->x0, a->x1, sectorno};
		init_edge(engine, engine->sectors[neighbor], a->wall);
	}
}

void			render_wall(t_engine *engine, int sectorno, int neighbor)
{
	render_init(engine, sectorno, neighbor);
	loop(engine, neighbor);
}

Uint32		get_pixel_color(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)(surface->pixels + y * surface->pitch
			+ (x % surface->w * surface->format->BytesPerPixel));
	rgb = p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void			render_vline1(t_engine *engine, t_line p, int txx, int dy)
{
	Uint32	*temp;

	temp = (Uint32 *)engine->screen->pixels;
	p.y0 = iclamp(p.y0, 0, H - 1);
	p.y1 = iclamp(p.y1, 0, H - 1);
	int step = dy;
	while (p.y0 < p.y1)
	{
		dy = dy >= engine->img[0].tx->h ? step : dy + step;
		temp[(p.y0 * W) + p.x0] = get_pixel_color(engine->img[0].tx, txx, dy);
		p.y0++;
	}
}
