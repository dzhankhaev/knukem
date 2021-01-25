/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hplane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		inloop(t_engine *engine, int *y_top, int x, int *x_table)
{
	(*y_top)++;
	render_hline(engine, *y_top, x_table[*y_top], x);
}

static void		inloop2(t_engine *engine, int *y_bot, int x, int *x_table)
{
	(*y_bot)--;
	render_hline(engine, *y_bot, x_table[*y_bot], x);
}

static void		loop(t_engine *engine, int *x_table, t_vplane *p, int x)
{
	int			y1;
	int			y2;
	int			*y_top;
	int			*y_bot;

	y_top = &engine->rend_plane.y_top;
	y_bot = &engine->rend_plane.y_bot;
	x--;
	while (++x <= p->maxx)
	{
		y1 = p->topy[x];
		y2 = p->boty[x];
		if (y2 < y1)
			continue ;
		while (y1 < *y_top)
			x_table[--(*y_top)] = x;
		while (y2 > *y_bot)
			x_table[++(*y_bot)] = x;
		while (*y_top < y1)
			inloop(engine, y_top, x, x_table);
		while (*y_bot > y2)
			inloop2(engine, y_bot, x, x_table);
	}
}

void			render_hplane(t_engine *engine, t_vplane *p, int txno)
{
	int			y;
	int			x_table[H];

	engine->rend_plane.y_top = p->topy[p->minx];
	engine->rend_plane.y_bot = p->boty[p->minx];
	engine->rend_plane.z = p->z;
	engine->rend_plane.tx = engine->img[txno].tx;
	y = engine->rend_plane.y_top;
	while (y <= engine->rend_plane.y_bot)
		x_table[y++] = p->minx;
	loop(engine, x_table, p, p->minx);
	y = engine->rend_plane.y_top;
	while (y <= engine->rend_plane.y_bot)
	{
		render_hline(engine, y, x_table[y], p->maxx);
		y++;
	}
}
