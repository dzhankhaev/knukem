#include "engine.h"
#include "events.h"

void	event_edit(t_player *player, t_edit *edit)
{
	if (player->event.key.keysym.sym == SDLK_1)
		edit->hchange[0] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->hchange[1] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_3)
		edit->hchange[2] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_4)
		edit->hchange[3] = player->event.type == SDL_KEYDOWN;
}