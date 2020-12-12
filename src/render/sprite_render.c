#include "engine.h"
#include "utilits.h"
#include "editor.h"

void	normi_sprite(t_sprites1 sprite, t_player player)
{
	sprite.weapon_sprite->translated_where.x = sprite.weapon_sprite->where.x - player.where.x;
	sprite.weapon_sprite->translated_where.y = sprite.weapon_sprite->where.y - player.where.y;
}

void	rotate_sprite(t_sprites1 sprite, t_player player)
{
	sprite.weapon_sprite->rotated_where.x = sprite.weapon_sprite->translated_where.x * player.anglecos +
			sprite.weapon_sprite->translated_where.y * player.anglesin;
	sprite.weapon_sprite->rotated_where.y = -sprite.weapon_sprite->translated_where.x * player.anglesin +
			sprite.weapon_sprite->translated_where.y * player.anglecos;
}

void	vrotate2(t_xyz p, float vangle) //используется для обработки вертикального угла взгляда
{
	p.z = p.z + p.x * vangle;
}

void	perspective_transform2(t_sprites1 sprite, t_player player)
{
	vrotate2(sprite.weapon_sprite->rotated_where, player.vangle);
	sprite.weapon_sprite->fin_transformed_where.x = (int)((W >> 1) + sprite.weapon_sprite->rotated_where.y
			/ sprite.weapon_sprite->rotated_where.x * (W >> 1));
	sprite.weapon_sprite->fin_transformed_where.y = (int)((H >> 1) + sprite.weapon_sprite->rotated_where.z
			/ sprite.weapon_sprite->rotated_where.x * (H >> 1));
}

double	scale_sprite(t_engine *engine, t_sprites1 *sprite)
{
	//int scale = 1/16;
	return squareRoot((square(engine->player.where.x) - square(sprite->weapon_sprite->where.x)) +
				(square(engine->player.where.y) - square(sprite->weapon_sprite->where.y)));
}

void	render_sprite(t_engine *engine)
{
	t_all temp;
	double scale;

    temp.sdl = &(t_sdl){engine->window, engine->screen};
	normi_sprite(*engine->sprites1, engine->player);
    rotate_sprite(*engine->sprites1, engine->player);
    perspective_transform2(*engine->sprites1, engine->player);
	scale = scale_sprite(engine, engine->sprites1);
	printf("\rscale = %f, player.x = %f, player.y = %f, trans.x = %f. trans.y = %f", scale, engine->player.where.x, engine->player.where.y,
	engine->sprites1->weapon_sprite->fin_transformed_where.x, engine->sprites1->weapon_sprite->fin_transformed_where.y);
	engine->sprites1->weapon_sprite->dstrect = (SDL_Rect){engine->sprites1->weapon_sprite->fin_transformed_where.x,
													   	engine->sprites1->weapon_sprite->fin_transformed_where.y,
													   W/scale, H/scale};
	//draw_fill_rect(&temp, engine->sprites1->weapon_sprite->dstrect, GREEN);
	draw_texture(temp.sdl, engine->sprites1->weapon_sprite->dstrect, engine->sprites1->weapon_sprite->texture);
}