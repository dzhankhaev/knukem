/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

void		init_ceil_floor(t_engine *engine, t_sect sector, t_line *wall)
{
	float	z;

	z = engine->player.where.z;
	wall[0] = perspective_transform(engine->wall, z - sector.ceil,
									engine->player.vangle, CEIL_COLOR);
	wall[1] = perspective_transform(engine->wall, z - sector.floor,
									engine->player.vangle, FLOOR_COLOR);
}

void		init_wall(t_engine *engine, t_sect sector, t_line *wall)
{
	float	z;

	z = engine->player.where.z;
	wall[2] = perspective_transform(engine->wall, z - sector.ceil,
									engine->player.vangle, TOP_COLOR);
	wall[3] = perspective_transform(engine->wall, z - sector.floor,
									engine->player.vangle, BOT_COLOR);
}
