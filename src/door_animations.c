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
			if (engine->sectors[dsec].door != -1)
			{
				if (anim == 0)
				{
					engine->sectors[dsec].door += 1;
					if (engine->player.sector == dsec)
						engine->sectors[dsec].door -= 1;
					engine->sectors[dsec].floor = engine->sectors[dsec].oldf + engine->sectors[dsec].door;
					if (engine->sectors[dsec].floor >= engine->sectors[dsec].ceil)
					{
						engine->danimbuf[i] = -1;
						engine->danimbuf[i + 1] = -1;
					}
				}
				if (anim == 1)
				{
					engine->sectors[dsec].door -= 1;
					if (engine->player.sector == dsec)
						engine->sectors[dsec].door += 1;
					engine->sectors[dsec].floor = engine->sectors[dsec].oldf + engine->sectors[dsec].door;
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

void 		put_anim(t_engine *engine, int sec)
{
	int	q;

	q = 0;
	while (q < 30)
	{
		if (engine->danimbuf[q] == -1)
		{
			engine->danimbuf[q] = sec;
			if (engine->sectors[sec].floor < engine->sectors[sec].ceil)
				engine->danimbuf[q + 1] = 0;
			else if (engine->sectors[sec].floor > engine->sectors[sec].oldf)
				engine->danimbuf[q + 1] = 1;
			else
				engine->danimbuf[q] = -1;
			break ;
		}
		q += 2;
	}
}

void		start_danim(t_engine *engine, int sec, int nei, int i)
{
	int	q;
	//если игрок смотрит на дверь
	if (engine->edit.mod_w == i && nei > -1 && nei == engine->edit.mod_s &&
		engine->edit.door == 2 && engine->sectors[nei].door > -1)
	{
		q = -2;
		//если данная дверь есть в очереди анимаций, не дублируем
		while (q < 30)
			if (engine->danimbuf[(q += 2)] == nei)
				return ;
		put_anim(engine, nei);
	}
	int left;
	int right;
	//если игрок смотрит на граффити
	if (engine->edit.door == 4)
	{
		engine->edit.door = 0;
		if (i == 0)
			left = engine->sectors[sec].neighbors[engine->sectors[sec].npoints - 1];
		else
			left = engine->sectors[sec].neighbors[i - 1];
		right = engine->sectors[sec].neighbors[i + 1];

		if (left > -1)
		{
			q = -2;
			while (q < 30)
				if (engine->danimbuf[(q += 2)] == left)
					return ;
			put_anim(engine, left);
		}

		if (right > -1)
		{
			q = -2;
			while (q < 30)
				if (engine->danimbuf[(q += 2)] == right)
					return ;
			put_anim(engine, right);
		}

	}
}