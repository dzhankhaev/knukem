#include "engine.h"

void	real_time_edit(t_engine *engine)
{
	int			*hchange;
	int			s;

	hchange = engine->edit.hchange;
	s = engine->edit.mod_s;
	if (s != 0x01ab01)
	{
		engine->sectors[s].floor -= hchange[0] * 1;
		engine->sectors[s].floor += hchange[1] * 1;
		engine->sectors[s].ceil -= hchange[2] * 1;
		engine->sectors[s].ceil += hchange[3] * 1;
	}
}