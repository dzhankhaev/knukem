#include "engine.h"
#include "utilits.h"

t_ixyz			tx_wall_mod(t_engine *engine, int sectorno, int i)
{
	t_ixyz	txset;
	int		q;
	int		k;

	txset = (t_ixyz){abs(engine->sectors[sectorno].neighbors[i]), 1, 2};
	if (engine->edit.mod_w != -1 && engine->edit.txno != -1)
	{
		if (engine->sectors[sectorno].neighbors[i] <= -1)
			engine->sectors[sectorno].neighbors[i] = engine->edit.txno * -1;
		if (engine->edit.mod_tx == 0)
			txset = (t_ixyz){abs(engine->sectors[sectorno].neighbors[i]), 1, 2};
		else if (engine->edit.mod_tx == 3)
			txset = (t_ixyz){0, engine->edit.txno, 2};
		else if (engine->edit.mod_tx == 4)
			txset = (t_ixyz){0, 1, engine->edit.txno};
	}
	return (txset);
}

t_ixyz			tx_plane_mod(t_engine *engine, int sectorno, int i)
{
	t_ixyz txset;

	txset = (t_ixyz){3, 4, 0};
	return (txset);
}