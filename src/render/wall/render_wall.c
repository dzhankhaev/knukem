#include "utilits.h"

void			render_vline1(t_engine *engine, t_line p, int dx, int dy);

static void		loop(t_engine *engine, t_line *wall, int x0, int x1, int *y, int neighbor)
{
	int		txx;
	t_line	w;
	int		x;
	//потребуется для вычисления света. Для других вычислений нужно упорядочить
	w = (t_line){wall[0].x0, wall[0].x1, wall[0].y0, wall[0].y1};
	to_x_order(wall);
	t_fline ew = engine->wall;
	x = x0;
	while (x < x1)
	{
//		X координата текстуры с учетом перспективы. ew.x - координата глубины. Остальные х - экранная координата ширины
//		https://en.wikipedia.org/wiki/Texture_mapping#Perspective_correctness
//		формула оптимизирована a = (x-wall[0].x0) / (wall[0].x1-wall[0].x0)
		txx = (engine->u0 * ((wall[0].x1 - x) * ew.x1) + engine->u1 * ((x - wall[0].x0) * ew.x0))
			  / ((wall[0].x1 - x) * ew.x1 + (x - wall[0].x0) * ew.x0);
		render_ceil_and_floor(engine, x, wall, y);
		if (neighbor != -1)
			render_edge(engine, x, wall, y, deep_shading(engine, w, x));
		else
		{
			render_vline1(engine,
						  (t_line){x, x, y[0], y[1], engine->wall.color},
						  txx,
						  1);
		}
		x++;
	}
}

void			render_wall(t_engine *engine, int sectorno, int neighbor)
{	//0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	//соседи отображаются нак грани текущего сектора, если они имеют общую грань
	t_line		wall[4];
	int			x0;
	int			x1;
	int			y[4];

	init_ceil_floor(engine, engine->sectors[sectorno], wall);
	//стены строго вертикально, потому у 0 и 1 иксы одинаковы
	x0 = imax(imin(wall[0].x0, wall[0].x1), engine->present->x0);			//заполняем в промежутке текущей стены
	x1 = imin(imax(wall[1].x0, wall[1].x1), engine->present->x1);			//иксы у пола и потолка всегда равны
	if (neighbor != -1)
	{
		if ((x1 > x0) && engine->future + 1 != engine->queue + engine->max_queue &&
			check_repeat(engine, sectorno, neighbor))
			*(engine->future++) = (t_queue){neighbor, x0, x1, sectorno};
		init_edge(engine, engine->sectors[neighbor], wall);
	}
	loop(engine, wall, x0, x1, y, neighbor);
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
