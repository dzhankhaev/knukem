/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

void	render_hline(t_engine *engine, int y, int xbegin, int xend)
{
	Uint32	*temp;
	t_temp2	*a;
	int		x;

	if (y < 0 || y >= H || xbegin < 0 || xbegin >= W || xend < 0 || xend >= W)
		return ;
	a = &engine->rend_plane;
	x = xbegin;
	temp = (Uint32 *)engine->screen->pixels;
	a->mapx = a->z / (((float)(y << 1) / H - 1) - engine->player.vangle);
	a->cosx = a->mapx * a->pcos;
	a->sinx = -a->mapx * a->psin;
	while (x < xend)
	{
		a->mapy = a->mapx * (((float)x - (W >> 1)) / (W >> 1));
		a->txy = abs((int)(((a->cosx + a->mapy * a->psin) +
				engine->player.where.x)
			* 256) % a->tx->h);
		a->txx = abs((int)(((a->sinx + a->mapy * a->pcos) +
				engine->player.where.y)
			* 256) % a->tx->w);
		temp[(y * W) + x] = get_shadow(engine->player.deep_sh * a->mapx
				* DEEP_SHADING, get_pixel_color(a->tx, a->txx, a->txy));
		x++;
	}
}
