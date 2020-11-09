#include "engine.h"
#include "events.h"

void	event_edit2(t_player *player, t_edit *edit)
{
	if (player->event.key.keysym.sym == SDLK_0)
		edit->txno = 0;
	else if (player->event.key.keysym.sym == SDLK_1)
		edit->txno = 1;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->txno = 2;
	else if (player->event.key.keysym.sym == SDLK_3)
		edit->txno = 3;
	else if (player->event.key.keysym.sym == SDLK_4)
		edit->txno = 4;
}

void	event_edit(t_player *player, t_edit *edit)
{
	if (player->event.key.keysym.sym == SDLK_o)
		edit->hchange[0] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_p)
		edit->hchange[1] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_j)
		edit->hchange[2] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_k)
		edit->hchange[3] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_1)
		edit->txno = 0;
	else if (player->event.key.keysym.sym == SDLK_1)
		edit->txno = 1;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->txno = 2;
	else if (player->event.key.keysym.sym == SDLK_1)
		edit->txno = 3;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->txno = 4;
}