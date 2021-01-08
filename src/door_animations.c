#include "engine.h"

void 		door_anim(t_engine *engine)
{
	int i;
	int dsec;
	int anim;

	i = 0;
	while (i < 30)
	{
		if (engine->danimbuf[i] != -1)
		{
			dsec = engine->danimbuf[i];
			anim = engine->danimbuf[i + 1];
			if (engine->sectors[dsec].doors != -1)
			{
				if (anim == 0)
				{
					engine->sectors[dsec].doors += 1;
					if (engine->player.sector == dsec)
						engine->sectors[dsec].doors -= 1;
					engine->sectors[dsec].floor = engine->sectors[dsec].oldf + engine->sectors[dsec].doors;
					if (engine->sectors[dsec].floor >= engine->sectors[dsec].ceil)
					{
						engine->danimbuf[i] = -1;
						engine->danimbuf[i + 1] = -1;
					}
				}
				if (anim == 1)
				{
					engine->sectors[dsec].doors -= 1;
					if (engine->player.sector == dsec)
						engine->sectors[dsec].doors += 1;
					engine->sectors[dsec].floor = engine->sectors[dsec].oldf + engine->sectors[dsec].doors;
					if (engine->sectors[dsec].floor <= engine->sectors[dsec].oldf)
					{
						engine->danimbuf[i] = -1;
						engine->danimbuf[i + 1] = -1;
					}
				}
			}
		}
		i += 2;
	}
}

void		start_danim(t_engine *engine, int nei, int i)
{
	int	q;
	//если игрок смотрит на дверь
	if (engine->edit.mod_w == i && nei > -1 && nei == engine->edit.mod_s &&
		engine->edit.door == 2 && engine->sectors[nei].doors > -1)
	{
		q = -2;
		//если данная дверь есть в очереди анимаций, не дублируем
		while (q < 30)
			if (engine->danimbuf[(q += 2)] == nei)
				return ;
		q = 0;
		while (q < 30)
		{
			if (engine->danimbuf[q] == -1)
			{
				engine->danimbuf[q] = nei;
				if (engine->sectors[nei].floor < engine->sectors[nei].ceil)
					engine->danimbuf[q + 1] = 0;
				else if (engine->sectors[nei].floor > engine->sectors[nei].oldf)
					engine->danimbuf[q + 1] = 1;
				else
					engine->danimbuf[q] = -1;
				break ;
			}
			q += 2;
		}
	}
}