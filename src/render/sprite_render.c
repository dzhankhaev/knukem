#include "engine.h"
#include "editor.h"

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
	draw_texture(temp.sdl, engine->sprites1->weapon_sprite->dstrect, engine->sprites1->weapon_sprite->texture);
}