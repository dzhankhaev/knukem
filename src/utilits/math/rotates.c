/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_fline			rotate_wall(t_fline wall, t_player player)
{
	t_fline	w;

	wall.x0 = wall.x0 - player.where.x;
	wall.y0 = wall.y0 - player.where.y;
	wall.x1 = wall.x1 - player.where.x;
	wall.y1 = wall.y1 - player.where.y;
	w = wall;
	wall.x0 = w.x0 * player.anglecos + w.y0 * player.anglesin;
	wall.x1 = w.x1 * player.anglecos + w.y1 * player.anglesin;
	wall.y0 = -w.x0 * player.anglesin + w.y0 * player.anglecos;
	wall.y1 = -w.x1 * player.anglesin + w.y1 * player.anglecos;
	return (wall);
}
