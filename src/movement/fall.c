/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	fall(t_player *player, t_sect *sectors)
{
	if (player->falling || player->flying)
	{
		player->velocity.z -= ((float)player->settings.gravity / 1000.f)
				* !player->flying;
		//если падаю вниз и если достиг пола - останавливаю падение и зануляю скорость
		if (player->velocity.z < 0 && player->where.z + player->velocity.z
					< sectors[player->sector].floor + player->eyeheight)
		{
			player->velocity.z = 0;
			player->falling = 0;
			player->ground = 1;
		}
		//если лечу вверх и если достиг потолка - зануляю скорость
		else if (player->velocity.z > 0 && player->where.z + player->velocity.z
										> sectors[player->sector].ceil)
			player->velocity.z = 0;
		player->where.z += player->velocity.z;
	}
	if (player->ground)
		player->where.z = sectors[player->sector].floor + player->eyeheight;
}
