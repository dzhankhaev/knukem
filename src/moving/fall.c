#include "engine.h"

void	fall(t_player *player, t_sector *sectors)
{
	if (player->falling)
	{
		player->velocity.z -= VACCEL;
		//если падаю вниз и если достиг пола - останавливаю падение и зануляю скорость
		if (player->velocity.z < 0 && player->where.z + player->velocity.z
		        < sectors[player->sector].floor + player->eyeheight)
		{
			player->velocity.z = 0;
			player->falling = 0;
		}
		//если лечу вверх и если достиг потолка - зануляю скорость
		else if (player->velocity.z > 0 && player->where.z + player->velocity.z
				> sectors[player->sector].ceil)
			player->velocity.z = 0;
		if (player->falling)
			player->where.z += player->velocity.z;
	}
	else
		player->where.z = sectors[player->sector].floor + player->eyeheight;
}