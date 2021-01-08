#include "engine.h"
#include "events.h"

<<<<<<< HEAD
void	event_edit2(t_player *player, t_edit *edit)
||||||| 1784372
void	event_edit(t_player *player, t_edit *edit)
=======
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
	else if (player->event.key.keysym.sym == SDLK_BACKQUOTE)
		edit->mod_tx = edit->mod_tx == 4 ? 0 : edit->mod_tx + 1;
}

void	event_edit(t_player *player, t_edit *edit)
>>>>>>> master
{
<<<<<<< HEAD
	if (player->event.key.keysym.sym == SDLK_1)
		edit->txno = 1;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->txno = 2;
	else if (player->event.key.keysym.sym == SDLK_3)
		edit->txno = 3;
	else if (player->event.key.keysym.sym == SDLK_4)
		edit->txno = 4;
	else if (player->event.key.keysym.sym == SDLK_BACKQUOTE)
		edit->mod_tx = edit->mod_tx == 4 ? 0 : edit->mod_tx + 1;
	else if (player->event.key.keysym.sym == SDLK_e)
		edit->mod = 1;
	else if (player->event.key.keysym.sym == SDLK_g)
		edit->graf++;
	else if (player->event.key.keysym.sym == SDLK_DELETE)
		edit->graf = 3;
	else if (player->event.key.keysym.sym == SDLK_h)
		edit->door = 1;
	else if (player->event.key.keysym.sym == SDLK_f)
		edit->door = 2;
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
||||||| 1784372
	if (player->event.key.keysym.sym == SDLK_1)
		edit->hchange[0] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->hchange[1] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_3)
		edit->hchange[2] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_4)
=======
	if (player->event.key.keysym.sym == SDLK_o)
		edit->hchange[0] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_p)
		edit->hchange[1] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_j)
		edit->hchange[2] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_k)
>>>>>>> master
		edit->hchange[3] = player->event.type == SDL_KEYDOWN;

}