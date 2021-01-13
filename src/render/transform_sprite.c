//
// Created by Denisse Gruyere on 12/17/20.
//

#include "engine.h"
#include "utilits.h"

t_fline		fov_sprite_cut(t_fline cut_sprite)
{
	t_xy	i1;
	t_xy	i2;

	//пересечение между лучом видимости и спрайтом
	i1 = intersection_point(cut_sprite,
							(t_fline){0, RAY_POINT_X, 0, -RAY_POINT_Y});
	i2 = intersection_point(cut_sprite,
							(t_fline){0, RAY_POINT_X, 0, RAY_POINT_Y});
	return (cut_wall(cut_sprite, i1, i2));
}

/*void		tex_init(t_engine *engine)	//	сопоставим координаты текстуры координатам стены после отрезания не попавших в кадр частей
{
	t_fline	w;
	t_fline	ow;

	w = engine->wall;
	ow = engine->ow;
	if (fabsf(w.y1 - w.y0) > fabsf(w.x1 - w.x0))
	{
		engine->u0 = (w.y0 - ow.y0) * engine->img[0].tx->w
					 / (ow.y1 - ow.y0);
		engine->u1 = (w.y1 - ow.y0) * engine->img[0].tx->w
					 / (ow.y1 - ow.y0);
	}
	else
	{
		engine->u0 = (w.x0 - ow.x0) * engine->img[0].tx->w
					 / (ow.x1 - ow.x0);
		engine->u1 = (w.x1 - ow.x0) * engine->img[0].tx->w
					 / (ow.x1 - ow.x0);
	}
}*/

static void choose_edit(t_engine *engine, int i)
{
	if (engine->edit.mod_s == 0x01ab01 &&
		determine_intersection(engine->wall, (t_fline){0, 50, 0, 0}))
	{
		engine->edit.mod_s =
				engine->sectors[engine->present->sectorno].neighbors[i];	//этот сектор можно модифицировать
		if (engine->edit.mod_w == -1)
			engine->edit.mod_w = i;
	}
}

void 	calculate_dist(t_sprites1 *sprites1)
{
	double x;
	double y;

	x = fabs(sprites1->weapon_sprite->translated_where.x);
	y = fabs(sprites1->weapon_sprite->translated_where.y);
	sprites1->weapon_sprite->dist = sqrt(x * x + y * y) < 1 ? 1 : sqrt(x * x + y * y);
	sprites1->weapon_sprite->height = H/sprites1->weapon_sprite->dist < 1 ? 1 : H/sprites1->weapon_sprite->dist;
	sprites1->weapon_sprite->width = W/sprites1->weapon_sprite->dist < 1 ? 1 : W/sprites1->weapon_sprite->dist;
}
//Считаем координаты краёв спрайта
void 	calculate_sprite_endings(t_sprites1 *sprites1, t_player player)
{
	double x0;
	double y0;
	double x1;
	double y1;
	double x3;
	double y3;
	double x4;
	double y4;

	x0 = player.where.x - sprites1->weapon_sprite->where.x; //мировые координаты игрока
	y0 = player.where.y - sprites1->weapon_sprite->where.y;
	x1 = sprites1->weapon_sprite->where.x; //мировые кооординаты спрайта
	y1 = sprites1->weapon_sprite->where.y;
	x3 = y0 + y1;
	y3 = x1 - x0;
	x4 = y1 - y0;
	y4 = x0 + x1;
	sprites1->weapon_sprite->cut_sprite_where = (t_fline){x3, x4, y3, y4, 0};
}

/*void		tex_init_sprite(t_engine *engine)	//	сопоставим координаты текстуры координатам стены после отрезания не попавших в кадр частей
{
	t_fline	w;
	t_fline	ow;

	w = engine->sprites1->weapon_sprite->cut_rotated_where;
	ow = engine->sprites1->weapon_sprite->fov_cut_rotated_where;
	if (fabsf(w.y1 - w.y0) > fabsf(w.x1 - w.x0))
	{
		engine->u0 = (w.y0 - ow.y0) * engine->sprites1->weapon_sprite->texture->w
					 / (ow.y1 - ow.y0);
		engine->u1 = (w.y1 - ow.y0) * engine->sprites1->weapon_sprite->texture->w
					 / (ow.y1 - ow.y0);
	}
	else
	{
		engine->u0 = (w.x0 - ow.x0) * engine->sprites1->weapon_sprite->texture->w
					 / (ow.x1 - ow.x0);
		engine->u1 = (w.x1 - ow.x0) * engine->sprites1->weapon_sprite->texture->w
					 / (ow.x1 - ow.x0);
	}
}*/

int		transform_sprite(t_engine *engine)
{
	t_fline cut_sprite;
	t_weapon_sprites *weaponSprites;

	weaponSprites = engine->sprites1->weapon_sprite;
	calculate_sprite_endings(engine->sprites1, engine->player);
	normi_sprite(*engine->sprites1, engine->player);
	rotate_sprite(*engine->sprites1, engine->player);
	perspective_transform2(*engine->sprites1, engine->player);
	calculate_dist(engine->sprites1);
	t_sdl sdl_temp = (t_sdl){engine->window, engine->screen};
	/*if (engine->wall.x0 <= 0 && engine->wall.x1 <= 0)
	{
		engine->wall.color = 0;
		return (0); //стены за спиной не рендерятся
	}*/
	//engine->ow = engine->wall;
	weaponSprites->fov_cut_rotated_where = fov_sprite_cut(engine->sprites1->weapon_sprite->cut_rotated_where);	//обрезаем частично попавшие в поле зрения стены
	draw_circle(&sdl_temp,
				(t_xy){W/2,H/2},
				2, BLACK);
	draw_circle(&sdl_temp,
				(t_xy){weaponSprites->cut_rotated_where.x0 * 3 + W/2,
					   weaponSprites->cut_rotated_where.y0 * 3 + H/2},
				3, RED);
	draw_circle(&sdl_temp,
				(t_xy){weaponSprites->cut_rotated_where.x1 * 3 + W/2,
					   weaponSprites->cut_rotated_where.y1 * 3 + H/2},
				3, RED);
	draw_circle(&sdl_temp,
				(t_xy){weaponSprites->rotated_where.x * 3 + W/2,
					   weaponSprites->rotated_where.y * 3 + H/2},
				3, GREEN);
	cut_sprite = weaponSprites->fov_cut_rotated_where;
    //printf("\rx0 = %f, y0 = %f, x1 = %f, y1 = %f", cut_sprite.x0, cut_sprite.y0, cut_sprite.x1, cut_sprite.y1);
    //printf("x3 = %f, y3 = %f, x4 = %f, y4 = %f", sprites1->weapon_sprite->cut_sprite_where.x, cut_sprite.y0, cut_sprite.x1, cut_sprite.y1);
    //printf("\r%i", ispointincube(3, engine->player.where, weaponSprites->where, 1));
    /*printf("ispc = %i, x = %f, y = %f, z = %f, \t\t\tsprite.X = %f, sprite.y = %f, sprite.z = %f\n",
           ispointincube(engine->player.where, weaponSprites->where, (t_xyz){2, 2, 20},0),
           engine->player.where.x, engine->player.where.y, engine->player.where.z,
           weaponSprites->where.x, weaponSprites->where.y, weaponSprites->where.z);*/
    if (ispointincube(engine->player.where, weaponSprites->where, (t_xyz){10, 10, 26},30)
        || cut_sprite.x0 <= 0 || cut_sprite.x1 <= 0
		|| cut_sprite.x0 * -K > cut_sprite.y0
		|| cut_sprite.x1 * K < cut_sprite.y1) {
        return (0);
    }
    /*if (engine->sprites1->weapon_sprite->rotated_where.x <= 0
        || engine->sprites1->weapon_sprite->rotated_where.x * -K >
           engine->sprites1->weapon_sprite->rotated_where.y)
        return (0); //то что не было отрезано и находится частично за спиной, а так же то что целиком лежит вне видимости тоже не рендерим.*/
    return (1);
}