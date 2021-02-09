/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:47:49 by ecelsa            #+#    #+#             */
/*   Updated: 2021/02/08 22:46:19 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"
#include "libft.h"

void		hud_put_num(int num, t_hud *hud, int x)
{
	hud->rect = (SDL_Rect){.x = x - 2, .y = 0};
	SDL_BlitSurface(hud->ammo_b, NULL, hud->scr, &hud->rect);
	if (num < 0)
	{
		num *= -1;
		hud->rect = (SDL_Rect){.x = x + 3 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[10], NULL, hud->scr, &hud->rect);
	}
	if (num / 100 > 0)
	{
		hud->rect = (SDL_Rect){.x = x + 0 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[num / 100], NULL, hud->scr, &hud->rect);
	}
	hud->rect = (SDL_Rect){.x = x + 1 * 14, .y = 4};
	SDL_BlitSurface(hud->num_h[(num / 10) % 10], NULL, hud->scr, &hud->rect);
	hud->rect = (SDL_Rect){.x = x + 2 * 14, .y = 4};
	SDL_BlitSurface(hud->num_h[num % 10], NULL, hud->scr, &hud->rect);
}

void		hud_put_cells(t_hud *hud, t_inp_hud *inp, t_hud_sub place, int par)
{
	int i;

	i = place.p_st;
	while (++i < place.p_col)
	{
		if (i < place.p_w)
			hud->rect = (SDL_Rect){.x = place.p_x + (i - 2) * place.p_dist,
																		.y = 4};
		else
			hud->rect = (SDL_Rect){.x = place.p_x + (i - place.p_dist2) *
														place.p_dist, .y = 14};
		if (par & (1 << (i - 1)))
			SDL_BlitSurface(hud->num_wp_y[i], NULL, hud->scr, &hud->rect);
		else
			SDL_BlitSurface(hud->num_wp_g[i], NULL, hud->scr, &hud->rect);
	}
}

void		put_hud_pis(t_hud *hud, SDL_Surface *scr, int b)
{
	int		coef;

	coef = scr->w / hud->hud->w;
	hud->rect = (SDL_Rect){.x = (scr->w - 42 - hud->pis[b]->w * coef) >> 1,
							.y = scr->h - scr->w / 10 - hud->pis[b]->h * coef,
						.w = hud->pis[b]->w * coef, .h = hud->pis[b]->h * coef};
	SDL_BlitScaled(hud->pis[b], NULL, scr, &hud->rect);
	if (b == 1)
	{
		hud->rect = (SDL_Rect){.x = ((scr->w - 42 - (hud->pis[b]->w - 72) *
				coef) >> 1), .y = scr->h - scr->w / 10 - (hud->pis[b]->h + 21) *
				coef, .w = hud->pis[5]->w * coef, .h = hud->pis[5]->h * coef};
		SDL_BlitScaled(hud->pis[5], NULL, scr, &hud->rect);
	}
}

void		put_hud(t_engine *engine)
{
	t_hud					*hud;
	t_inp_hud				*inp;
	static int				b = 0;

	hud = &engine->hud;
	inp = &engine->hud_inp;
	engine->hud.health = inp->health;
	hud->weapon = inp->weapons;
	hud->face = inp->face;
	SDL_BlitSurface(hud->scr, NULL, hud->hud, NULL);
	hud_check_next_frame(&b, hud, inp);
	hud_put_num(inp->health * -1, hud, 49);
	hud_put_num(inp->ammo, hud, 2);
	hud->rect = (SDL_Rect){.x = 104, .y = 0};
	SDL_BlitSurface(hud->arms, NULL, hud->scr, &hud->rect);
	hud_put_cells(hud, inp, (t_hud_sub){.p_w = 5, .p_col = 8, .p_dist = 12,
							.p_dist2 = 5, .p_x = 111, .p_st = 1}, inp->weapons);
	hud_put_cells(hud, inp, (t_hud_sub){.p_w = 6, .p_col = 10, .p_dist = 11,
							.p_dist2 = 7, .p_x = 194, .p_st = 0}, inp->buttons);
	hud->rect = (SDL_Rect){.x = 148, .y = 2};
	SDL_BlitSurface(hud->face_s[2], NULL, hud->scr, &hud->rect);
	put_hud_pis(hud, engine->screen, b);
	hud->rect = (SDL_Rect){.x = 0, .y = engine->screen->h - engine->screen->w /
					10, .w = engine->screen->w, .h = engine->screen->w / 10};
	SDL_BlitScaled(hud->scr, NULL, engine->screen, &hud->rect);
}
