#include "engine.h"

void	fall(t_player *player, t_sector *sectors)
{
	player->ground = !player->falling;
	if (player->falling)
	{
		player->velocity.z -= 0.05f; /* Add gravity */
		float nextz = player->where.z + player->velocity.z;
		if (player->velocity.z < 0 && nextz < sectors[player->sector].floor + player->eyeheight) // When going down
		{
			/* Fix to ground */
			player->where.z = sectors[player->sector].floor + player->eyeheight;
			player->velocity.z = 0;
			player->falling = 0;
			player->ground  = 1;
		}
		else if (player->velocity.z > 0 && nextz > sectors[player->sector].ceil) // When going up
		{
			/* Prevent jumping above ceiling */
			player->velocity.z = 0;
			player->falling = 1;
		}
		if (player->falling)
		{
			player->where.z += player->velocity.z;
//			moving = 1;
		}
	}
	else
		player->where.z = sectors[player->sector].floor + player->eyeheight;
}