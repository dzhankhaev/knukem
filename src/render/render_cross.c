/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cross.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	one(t_engine *engine, int h, int w)
{
	render_line((t_line){w - 20, w + 20, h - 2,
				h - 2, 0}, engine->screen, engine->borders);
	render_line((t_line){w - 20, w + 20, h + 1,
				h + 1, 0}, engine->screen, engine->borders);
	render_line((t_line){w - 20, w - 20, h - 2,
				h + 1, 0}, engine->screen, engine->borders);
	render_line((t_line){w + 20, w + 20, h - 2,
				h + 1, 0}, engine->screen, engine->borders);
	render_line((t_line){w - 2, w - 2, h - 20,
				h + 20, 0}, engine->screen, engine->borders);
	render_line((t_line){w + 1, w + 1, h - 20,
				h + 20, 0}, engine->screen, engine->borders);
	render_line((t_line){w - 2, w + 1, h - 20,
				h - 20, 0}, engine->screen, engine->borders);
	render_line((t_line){w - 2, w + 1, h + 20,
				h + 20, 0}, engine->screen, engine->borders);
	render_line((t_line){w - 19, w + 19, h - 1,
				h - 1, 0xffffff}, engine->screen, engine->borders);
}

void		render_cross(t_engine *engine)
{
	int	w;
	int	h;

	w = W >> 1;
	h = (H >> 1) - 30;
	one(engine, h, w);
	render_line((t_line){w - 19, w + 19, h,
				h, 0xffffff}, engine->screen, engine->borders);
	render_line((t_line){w - 1, w - 1, h - 19,
				h + 19, 0xffffff}, engine->screen, engine->borders);
	render_line((t_line){w, w, h - 19,
				h + 19, 0xffffff}, engine->screen, engine->borders);
}
