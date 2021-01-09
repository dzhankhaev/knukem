#include "engine.h"

void	anim_delete(t_engine *engine, int i)
{
	engine->danimbuf[i] = -1;
	engine->danimbuf[i + 1] = -1;
}