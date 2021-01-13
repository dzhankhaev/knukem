#include "engine.h"
#include "editor.h"
#include "utilits.h"

void	normi_sprite(t_sprites1 sprite, t_player player)
{
	sprite.weapon_sprite->translated_where.x = sprite.weapon_sprite->where.x - player.where.x;
	sprite.weapon_sprite->translated_where.y = sprite.weapon_sprite->where.y - player.where.y;
	sprite.weapon_sprite->cut_translated_where.x0 = sprite.weapon_sprite->cut_sprite_where.x0 - player.where.x;
	sprite.weapon_sprite->cut_translated_where.y0 = sprite.weapon_sprite->cut_sprite_where.y0 - player.where.y;
	sprite.weapon_sprite->cut_translated_where.x1 = sprite.weapon_sprite->cut_sprite_where.x1 - player.where.x;
	sprite.weapon_sprite->cut_translated_where.y1 = sprite.weapon_sprite->cut_sprite_where.y1 - player.where.y;

}

void	rotate_sprite(t_sprites1 sprite, t_player player)
{
	sprite.weapon_sprite->rotated_where.x = sprite.weapon_sprite->translated_where.x * player.anglecos +
											sprite.weapon_sprite->translated_where.y * player.anglesin;
	sprite.weapon_sprite->rotated_where.y = -sprite.weapon_sprite->translated_where.x * player.anglesin +
											 sprite.weapon_sprite->translated_where.y * player.anglecos;
	sprite.weapon_sprite->cut_rotated_where.x0 = sprite.weapon_sprite->cut_translated_where.x0 * player.anglecos +
												 sprite.weapon_sprite->cut_translated_where.y0 * player.anglesin;
	sprite.weapon_sprite->cut_rotated_where.y0 = -sprite.weapon_sprite->cut_translated_where.x0 * player.anglesin +
												 sprite.weapon_sprite->cut_translated_where.y0 * player.anglecos;
	sprite.weapon_sprite->cut_rotated_where.x1 = sprite.weapon_sprite->cut_translated_where.x1 * player.anglecos +
												 sprite.weapon_sprite->cut_translated_where.y1 * player.anglesin;
	sprite.weapon_sprite->cut_rotated_where.y1 = -sprite.weapon_sprite->cut_translated_where.x1 * player.anglesin +
												 sprite.weapon_sprite->cut_translated_where.y1 * player.anglecos;
}

void	vrotate2(t_sprites1 *sprite, t_player player) //используется для обработки вертикального угла взгляда
{
	sprite->weapon_sprite->rotated_where.z = player.where.z - sprite->weapon_sprite->where.z +
			sprite->weapon_sprite->rotated_where.x * player.vangle;
}

void	perspective_transform2(t_sprites1 sprite, t_player player)
{
	vrotate2(&sprite, player);
	sprite.weapon_sprite->fin_transformed_where.x = (int)((W >> 1) + sprite.weapon_sprite->rotated_where.y
			/ sprite.weapon_sprite->rotated_where.x * (W >> 1));
	sprite.weapon_sprite->fin_transformed_where.y = (int)((H >> 1) + sprite.weapon_sprite->rotated_where.z
			/ sprite.weapon_sprite->rotated_where.x * (H >> 1));
	sprite.weapon_sprite->cut_fin_transformed_where.x0 = (int)((W >> 1) + sprite.weapon_sprite->cut_rotated_where.y0
																	 / sprite.weapon_sprite->cut_rotated_where.x0 * (W >> 1));
	sprite.weapon_sprite->cut_fin_transformed_where.y0 = (int)((H >> 1) + sprite.weapon_sprite->rotated_where.z					//Координата z (cut) совпадает с z спрайта
																	 / sprite.weapon_sprite->cut_rotated_where.x0 * (H >> 1));
	sprite.weapon_sprite->cut_fin_transformed_where.x1 = (int)((W >> 1) + sprite.weapon_sprite->cut_rotated_where.y1
																	 / sprite.weapon_sprite->cut_rotated_where.x1 * (W >> 1));
	sprite.weapon_sprite->cut_fin_transformed_where.y1 = (int)((H >> 1) + sprite.weapon_sprite->rotated_where.z
																	 / sprite.weapon_sprite->cut_rotated_where.x1 * (H >> 1));
}

/*
 * Получаем точку (вершину) начала отрезка (края сектора) с которым пересекается отрезок игрок-спрайт
 * */
int get_intersection_wall_player_vertex(t_engine *engine, int sectorno)
{
    int		i;
    //int		sectorno;
    t_fline wall;
    t_fline plsprline;

    i = 0;
    //sectorno = engine->present->sectorno;
    /*
     * Проверяем все вершины сектора (т.е. все края сектора) на пересечение отрезком игрок-спрайт
     * */
    while (i < engine->sectors[sectorno].npoints)
    {
        wall = (t_fline){
                engine->sectors[engine->present->sectorno].vertex[i].x,
                engine->sectors[engine->present->sectorno].vertex[i + 1].x,
                engine->sectors[engine->present->sectorno].vertex[i].y,
                engine->sectors[engine->present->sectorno].vertex[i + 1].y,
                0};
        plsprline = (t_fline){engine->player.where.x, engine->sprites1->weapon_sprite->where.x,
                              engine->player.where.y, engine->sprites1->weapon_sprite->where.y, 0};
        if (determine_intersection(wall, plsprline))
            return (i);
        i++;
    }
    /*
     * Почему-то такие пересечения находятся не всегда /TODO
     * */
    return (-1);
}

/*
 * Функция проверяет пересечение отрезка игрок-спрайт с отрезком края сектора (отрезок между двумя вершинами)
 * */
int is_sprite_visible(t_engine *engine)
{
	int wallvertex;
	int sectorno;
	int neighbour_sect;

	sectorno = engine->present->sectorno;
	/*
	 * Находим точку (вершину) начала отрезка у с которым пересекается отрезок игрок-спрайт
	 * Иногда такой вершины не находится. Почему - непонятно \TODO
	 * */
	if ((wallvertex = get_intersection_wall_player_vertex(engine, sectorno)) < 0)
	{
		printf("AAAAAAAAAA\n");
		return (1);
	}
	/*
	 * Если пересекаемый край сектора стена, то спрайт рендерить не нужно
	 * */
	if ((neighbour_sect = engine->sectors[sectorno].neighbors[wallvertex]) < 0)
	{
		printf("BBBBBBBBBB\n");
		return (0);
	}
	/*
	 * Последовательно проверяем все сектора вдоль отрезка игрок-спрайт
	 * Здесь фризит при пересечении сектора \TODO
	 * */
	while (sectorno != engine->sprites1->weapon_sprite->sector)
	{
		printf("FREEEEEEEZY\n");
		if (neighbour_sect < 0)
		{
			printf("CCCCCCCCC\n");
			return (0);
		}
		else
		{
			sectorno = neighbour_sect;
			wallvertex = get_intersection_wall_player_vertex(engine, sectorno);
			neighbour_sect = engine->sectors[sectorno].neighbors[wallvertex];
		}
	}
	/*
	 * Если пересечения со стеной не произошло, то спрайт виден.
	 * */
	printf("DDDDDDDDD\n");
	return (1);
}

void	render_sprite(t_engine *engine)
{
	t_all temp;
	t_sprites1 *sprite;

	sprite = engine->sprites1;
    temp.sdl = &(t_sdl){engine->window, engine->screen};
	/*
	 	printf("\rscale = %f, player.x = %f, player.y = %f, player.z = %f, player.vangle = %f, player.sector = %i, trans.x = %f. trans.y = %f",
		scale,
		engine->player.where.x,
		engine->player.where.y,
		engine->player.where.z,
		engine->player.vangle,
		engine->player.sector,
		engine->sprites1->weapon_sprite->fin_transformed_where.x,
		engine->sprites1->weapon_sprite->fin_transformed_where.y);*/

	engine->sprites1->weapon_sprite->dstrect = (SDL_Rect){sprite->weapon_sprite->fin_transformed_where.x,
													   	sprite->weapon_sprite->fin_transformed_where.y,
													   sprite->weapon_sprite->width, sprite->weapon_sprite->height};
	//draw_fill_rect(&temp, engine->sprites1->weapon_sprite->dstrect, GREEN);
	/*if (engine->sprites1->weapon_sprite->rotated_where.x <= 0
		|| engine->sprites1->weapon_sprite->rotated_where.x * -K >
		engine->sprites1->weapon_sprite->rotated_where.y)
		return ;*/
<<<<<<< HEAD
	/*
	 * Проверяем видимость спрайта сквозь стены и затем рендерим его
	 * */
	if (is_sprite_visible(engine))
	    draw_texture(temp.sdl, engine->sprites1->weapon_sprite->dstrect, engine->sprites1->weapon_sprite->texture);
||||||| f716230
	draw_texture(temp.sdl, engine->sprites1->weapon_sprite->dstrect, engine->sprites1->weapon_sprite->texture);
=======
	draw_texture(temp.sdl->screen, engine->sprites1->weapon_sprite->dstrect, engine->sprites1->weapon_sprite->texture);
>>>>>>> 28ac88b609aa0686d0a9dc5fa50fcdf55f8579a8
}