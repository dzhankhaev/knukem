/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

void		render_vline(t_engine *engine, t_line p, t_line op, int texture_n)
{
	Uint32	*temp;
	int		txy;
	int		t;
	t_temp	*a;
	int		txx;

	if (p.x0 < 0 || p.x1 >= W || op.y1 - op.y0 == 0)
		return ;
	temp = (Uint32 *)engine->screen->pixels;
	a = &engine->rend_wall;
	p.y0 = iclamp(p.y0, 0, H - 1);
	p.y1 = iclamp(p.y1, 0, H - 1);
	t = op.y1 - op.y0;
	txx = abs(a->txx % engine->img[texture_n].tx->w);
	while (p.y0 < p.y1)
	{
		txy = abs(((p.y0 - op.y0) * engine->img[texture_n].tx->h / t)
			% engine->img[texture_n].tx->h);
		temp[(p.y0 * W) + p.x0] = get_shadow(a->z,
			get_pixel_color(engine->img[texture_n].tx, txx, txy));
		p.y0++;
	}
}
