/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

t_line			swap_coords(t_line p)
{
	int t;

	t = p.x0;
	p.x0 = p.x1;
	p.x1 = t;
	t = p.y0;
	p.y0 = p.y1;
	p.y1 = t;
	return (p);
}

void			to_x_order(t_line *wall)
{
	if (wall[0].x0 > wall[0].x1)
		wall[0] = swap_coords(wall[0]);
	if (wall[1].x0 > wall[1].x1)
		wall[1] = swap_coords(wall[1]);
	if (wall[2].x0 > wall[2].x1)
		wall[2] = swap_coords(wall[2]);
	if (wall[3].x0 > wall[3].x1)
		wall[3] = swap_coords(wall[3]);
}
