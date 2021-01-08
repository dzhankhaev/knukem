#include "engine.h"
//соседи потенциальной двери не должны быть дверьми
static int	check_nei(t_engine *engine, int neighbor)
{
	int	q;
	int	s;

	q = 0;
	while (q < engine->sectors[neighbor].npoints)
	{
		s = engine->sectors[neighbor].neighbors[q];
		if (s != -1)
			if (engine->sectors[s].door != -1)
				return (0);
		q++;
	}
	return (1);
}

void		door_mod(t_engine *engine, int neighbor, int i)
{
	//если стена модифицируема и является порталом установить её как дверь
	//doors столько же сколько и neighbors.
	//Нужно внести инфу о двери в текущий сектор и в соседние сектора дверного сектора
	//В дверной сектор нужно внести инфу о высоте пола
	int q;

	if (engine->edit.mod_w == i && neighbor > -1
		&& neighbor == engine->edit.mod_s && engine->edit.door == 1)
	{
		q = -2;
		//если запущена анимация, дверь не трогать
		while (q < 30)
			if (engine->danimbuf[(q += 2)] == neighbor)
				return ;
		if (engine->sectors[neighbor].door == -1 && check_nei(engine, neighbor))
			engine->sectors[neighbor].door = 0;
		else
		{
			engine->sectors[neighbor].door = -1;
			engine->sectors[neighbor].floor = engine->sectors[neighbor].oldf;
		}
	}
}
