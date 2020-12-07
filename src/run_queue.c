#include <utilits.h>
#include "engine.h"

static int	get_color(t_engine *engine, unsigned s, int color)
{
	if (fabsf(engine->sectors[s].floor
			  - engine->sectors[engine->player.sector].floor) < FLOOR_DIFF)
		return (color);
	return (0);
}

int				check_repeat(t_engine *engine, int sectorno, int neighbor)
{
	t_queue *temp;

	temp = engine->queue;
	while (temp != engine->future)
	{
		/*
		 * мы перемещаемся из А в В. Если в очереди был переход из В в А, то это возврат назад. Так делать нельзя.
		 * это справедливо для выпуклых секторов
		 */
		if (temp->psec == neighbor && temp->sectorno == sectorno)
			return (0);
		temp++;
	}
	return (1);
}

void 		run_queue(t_engine *engine)
{
	int		i;
	int		sectorno;
	int		color;
	t_xy	size;
	float	sprite_ratio;
	int 	x1;
	int 	y1;
	int		x2;
	int		y2;
	int		xrange;
	int		yrange;
	int		xstart;
	int		ystart;
	int		xend;
	int		yend;
	int 	left;
	int 	right;
	int 	top;
	int 	bottom;
	float	xalpha;
	float 	yalpha;
	int		textx;
	int		texty;

	i = 0;
	sectorno = engine->present->sectorno;
	while (i < engine->sectors[sectorno].npoints)
	{
		if (engine->sprites1.weapon_sprite->sector == sectorno)
		{
			get_rotated_sprite_pos(engine);
			project_enemy(engine);
			size.x =  W / engine->sprites1.weapon_sprite->rotated_where.z;
			sprite_ratio = engine->sprites1.weapon_sprite->dstrect.w
						   / (double)engine->sprites1.weapon_sprite->dstrect.h;
			size.y = size.x * sprite_ratio;
			x1 = engine->screen_pos.x - size.y / 4;
			x2 = engine->screen_pos.x + size.y / 4;
			y1 = engine->screen_pos.y - size.x / 2;
			y2 = engine->screen_pos.y;
			xstart = clamp(x1, 0, W - 1);
			ystart = clamp(y1 + 1, 0, H - 1);
			xend = clamp(2, 0, W - 1);
			yend = clamp(2, 0, H - 1);
			left = xstart;
			right = xend;
			top = ystart;
			bottom = yend;
			xrange = x2 - x1;
			yrange = y2 - y1;
			while (xstart <= xend)
			{
				xalpha = (xstart - x1) / xrange;
				textx = 0 + xalpha * engine->sprites1.weapon_sprite->texture->w;;
				while (ystart < yend)
				{
					draw_vline_enemy(orender, &drawer, env);
					ystart++;
				}
				xstart++;
			}
			//draw_texture(engine);
		}
		if (engine->sectors[sectorno].neighbors[i] <= -1)
			engine->wall.color = WALL_COLOR;
		else
			engine->wall.color = EDGE_COLOR;
		color = engine->wall.color;
		if (transform_wall(engine, i)) //Проецирование стены в поле зрения игрока
			render_scene(engine, sectorno,    //текущий сектор
						 engine->sectors[sectorno].neighbors[i], i);		//его сосед, границу с которым мы обрабатываем.
		if (engine->minimap.mod)
			minimap(engine, engine->sectors[sectorno].vertex[i],
					engine->sectors[sectorno].vertex[i + 1], color);
		else
			minimap_cut(engine, (t_xy){engine->wall.x0, engine->wall.y0},
						(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
		i++;
	}
}