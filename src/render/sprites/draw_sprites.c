//
// Created by Denisse Gruyere on 12/6/20.
//

#include "engine.h"

void	get_translated_sprite_pos(t_engine *engine)
{
	engine->sprites1.weapon_sprite->translated_where.x = engine->sprites1.weapon_sprite->where.x - engine->player.where.x;
	engine->sprites1.weapon_sprite->translated_where.y = engine->sprites1.weapon_sprite->where.y - engine->player.where.y;
	engine->sprites1.weapon_sprite->translated_where.z = engine->sprites1.weapon_sprite->where.z - engine->player.where.z;
}

void	get_rotated_sprite_pos(t_engine *engine)
{
	get_translated_sprite_pos(engine);
	engine->sprites1.weapon_sprite->rotated_where.x = engine->sprites1.weapon_sprite->translated_where.x
													  * engine->player.anglesin
													  - engine->sprites1.weapon_sprite->translated_where.x
														* engine->player.anglecos;
	engine->sprites1.weapon_sprite->rotated_where.z = engine->sprites1.weapon_sprite->translated_where.x
													  * engine->player.anglecos
													  - engine->sprites1.weapon_sprite->translated_where.z
														* engine->player.anglesin;
	engine->sprites1.weapon_sprite->rotated_where.y = engine->sprites1.weapon_sprite->translated_where.y
													  + engine->sprites1.weapon_sprite->rotated_where.z
														* engine->player.vangle;
}

void	project_enemy(t_engine *engine)
{
	engine->screen_pos.y = H + (engine->sprites1.weapon_sprite->rotated_where.y
							/ -engine->sprites1.weapon_sprite->rotated_where.z);
	engine->screen_pos.x = W + (engine->sprites1.weapon_sprite->rotated_where.x
							/ -engine->sprites1.weapon_sprite->rotated_where.z);
}

/*
 * * Для нескольких спрайтов
 */

/*int		get_enemy_relative_pos(void *param)
{
	t_env		*env;
	t_camera	*camera;
	int			i;
	int			max;

	env = ((t_enemy_thread*)param)->env;
	i = ((t_enemy_thread*)param)->xstart;
	max = ((t_enemy_thread*)param)->xend;
	camera = ((t_enemy_thread*)param)->camera;
	while (i < max)
	{
		get_translated_enemy_pos(camera,
								 &env->enemies[env->rendered_enemies[i]]);
		get_rotated_enemy_pos(camera, &env->enemies[env->rendered_enemies[i]]);
		i++;
	}
	return (0);
}*/



