/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tx_mod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_ixyz			tx_wall_mod(t_engine *engine, int sectorno, int i)
{
	if (engine->edit.mod_w != -1 && engine->edit.txno != -1
									&& engine->edit.txno != 0
	&& !engine->edit.graf && engine->player.game_mode)
	{
		if (engine->sectors[sectorno].neighbors[i] <= -1
		&& engine->edit.mod_tx == 2)
			engine->sectors[sectorno].neighbors[i] = engine->edit.txno * -1;
		else if (engine->edit.mod_tx == 3)
			engine->sectors[sectorno].txw0 = engine->edit.txno;
		else if (engine->edit.mod_tx == 4)
			engine->sectors[sectorno].txw1 = engine->edit.txno;
	}
	return ((t_ixyz){abs(engine->sectors[sectorno].neighbors[i]),
			engine->sectors[sectorno].txw0, engine->sectors[sectorno].txw1});
}

t_ixyz			tx_plane_mod(t_engine *engine, int sectorno)
{
	if (engine->edit.txno != -1 && !engine->edit.graf
	&& engine->player.game_mode && engine->edit.txno != 0)
	{
		if (engine->edit.mod_tx == 0)
		{
			engine->sectors[sectorno].txf = engine->edit.txno;
			engine->edit.txno = -1;
		}
		else if (engine->edit.mod_tx == 1)
		{
			engine->sectors[sectorno].txc = engine->edit.txno;
			engine->edit.txno = -1;
		}
	}
	return ((t_ixyz){engine->sectors[engine->vpfloor.s].txf,
			engine->sectors[engine->vpfloor.s].txc, 0});
}
