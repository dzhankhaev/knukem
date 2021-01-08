#include "engine.h"

void	real_time_edit(t_engine *engine)
{
	int			*hchange;
	int			s;

	hchange = engine->edit.hchange;
	s = engine->edit.mod_s;
	if (s != 0x01ab01 && engine->sectors[s].door == -1)
	{
		engine->sectors[s].floor -= hchange[0] * 1;
		if (engine->sectors[s].floor < 0)
			engine->sectors[s].floor += hchange[0] * 1;
		engine->sectors[s].floor += hchange[1] * 1;
		if (engine->sectors[s].floor > engine->sectors[s].ceil)
			engine->sectors[s].floor -= hchange[1] * 1;
		engine->sectors[s].ceil -= hchange[2] * 1;
		if (engine->sectors[s].ceil < engine->sectors[s].floor)
			engine->sectors[s].ceil += hchange[2] * 1;
		engine->sectors[s].ceil += hchange[3] * 1;
		if (engine->sectors[s].ceil > 100)
			engine->sectors[s].ceil -= hchange[3] * 1;
		engine->sectors[s].oldf = engine->sectors[s].floor;
	}
}