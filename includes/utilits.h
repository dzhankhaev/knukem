#ifndef UTILITS_H
# define UTILITS_H

#include "engine.h"

float			point_side(float px, float py, t_xy vert, t_xy vert1);
int				y_for_x(t_line wall, int x);
float			vector_cross_product(float x0, float y0, float x1, float y1);
int				imax(int a, int b);
int				imin(int a, int b);
float			clamp(float a, float min, float max);
int				iclamp(int a, int min, int max);
t_line			swap_coords(t_line p);
void			to_x_order(t_line *wall);
t_xy			intersection_point(t_fline wall, t_fline twall);
int				determine_intersection(t_fline wall, t_fline twall);
t_fline			rotate_wall(t_sector sector, t_player player, int i, int color);
t_line			perspective_transform(t_fline w, float z, float yaw, int color);
void			exc(const char *file, const char *function);
void			clean(t_engine *engine);
void 			load_img(t_engine *engine, char *name, int n);
void			get_filename(t_engine *engine, char *name, int n);
Uint32			get_pixel_color(SDL_Surface *surface, int x, int y);

#endif

/*
#include "utilits.h"

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

static void		loop(t_engine *engine, int neighbor)
{
	t_temp	*a;

	a = &engine->rend_wall;
	//потребуется для вычисления света и текстур. Для других вычислений нужно упорядочить
	a->w = a->wall[0];
	to_x_order(a->wall);
	a->l = engine->wall;
	a->x = a->x0;
	while (a->x < a->x1)
	{
//		X координата текстуры с учетом перспективы. ew.x - координата глубины. Остальные х - экранная координата ширины
//		https://en.wikipedia.org/wiki/Texture_mapping#Perspective_correctness
//		формула оптимизирована a = (x-wall[0].x0) / (wall[0].x1-wall[0].x0)
		a->txx = (engine->u0 * ((a->w.x1 - a->x) * a->l.x1)
				+ engine->u1 * ((a->x - a->w.x0) * a->l.x0))
				/ ((a->w.x1 - a->x) * a->l.x1 + (a->x - a->w.x0) * a->l.x0);
		render_ceil_and_floor(engine);		//y[0] и y[1] мы получаем тут путем линейной интерполяции
		render_edge(engine, neighbor, deep_shading(engine, a->w, a->x));
		a->x++;
	}
//	render_line((t_line){a->wall[1].x0, a->wall[1].x1,a->wall[1].y0,a->wall[1].y1, 0x00ff00}, engine->screen, engine->borders);
}

void			render_wall(t_engine *engine, int sectorno, int neighbor)
{
	render_init(engine, sectorno, neighbor);
	loop(engine, neighbor);
}


 */