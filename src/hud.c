/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:47:49 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/05 02:26:07 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "libft.h"

typedef struct	s_hud
{
	SDL_Surface		*scr;
	SDL_Rect		rect;
	int				health;
	int				weapons;
	int				face;
	SDL_Surface		*hud;
	SDL_Surface		*arms;
	SDL_Surface		*pis[6];
	SDL_Surface		*num_h[11];
	SDL_Surface		*num_wp_g[10];
	SDL_Surface		*num_wp_y[10];
	SDL_Surface		*face_s[3];
}				t_hud;

int				load_hud_face_pis_yenum(t_hud *hud, char *file_name, int len, int i)
{
	ft_strcpy(file_name + len, "STFST00.png");
	hud->face_s[0] = IMG_Load(file_name);
	ft_strcpy(file_name + len, "STFST01.png");
	hud->face_s[1] = IMG_Load(file_name);
	ft_strcpy(file_name + len, "STFST02.png");
	hud->face_s[2] = IMG_Load(file_name);
	ft_strcpy(file_name + len, "PISGA0.png");
	while (++i < 5)
	{
		file_name[len + 4] = 'A' + i;
		hud->pis[i] = IMG_Load(file_name);
	}
	ft_strcpy(file_name + len, "PISFA0.png");
	hud->pis[5] = IMG_Load(file_name);
	ft_strcpy(file_name + len, "STYSNUM .png");
	i = -1;
	while (++i < 10)
	{
		file_name[len + 7] = i + '0';
		hud->num_wp_y[i] = IMG_Load(file_name);
	}
	return (1);
}

int				load_hud_hnum_gnum(t_hud *hud, char *file_name, int len, int i)
{
	ft_strcpy(file_name + len, "STGNUM .png");
	while (++i < 11)
	{
		if (i < 10)
		{
			file_name[len + 2] = 'G';
			file_name[len + 6] = i + '0';
			hud->num_wp_g[i] = IMG_Load(file_name);
			file_name[len + 2] = 'T';
		}
		else
			ft_strcpy(file_name + len, "STTPRCNT.png");
		hud->num_h[i] = IMG_Load(file_name);
	}
	return (1);
}

t_hud			*load_surfaces(const char *dirs)
{
	t_hud	*hud;
	char	*file_name;
	int		len;
	int		i;

	hud = (t_hud*)malloc(sizeof(t_hud));
	hud->health = -1;
	hud->weapons = -1;
	hud->face = -1;
	len = ft_strlen(dirs);
	file_name = (char*)malloc(len + 13);
	ft_strcpy(file_name, dirs);
	ft_strcpy(file_name + len, "STBAR.png");
	hud->hud = IMG_Load(file_name);
	hud->scr = SDL_CreateRGBSurface(0, 320, 32, 32,
											0xff0000, 0xff00, 0xff, 0xff000000);
	SDL_BlitSurface(hud->hud, NULL, hud->scr, NULL);
	load_hud_face_pis_yenum(hud, file_name, len, -1);
	load_hud_hnum_gnum(hud, file_name, len, -1);
	free(file_name);
	return (hud);
}

void			put_hud(SDL_Surface *scr, int health, int weapon, int face)
{
	static t_hud	*hud = NULL;
	int				b;
	int				i;
	int				coef;

	b = 0;
	if (hud == NULL)
		hud = load_surfaces("textur/");
	if (health != hud->health || weapon != hud->weapons || face != hud->face)
	{
		SDL_BlitSurface(hud->scr, NULL, hud->hud, NULL);
		if (health / 100 > 0)
		{
			hud->rect = (SDL_Rect){.x = 49 + 0 * 14, .y = 4};
			SDL_BlitSurface(hud->num_h[health / 100], NULL, hud->scr, &hud->rect);
		}
		hud->rect = (SDL_Rect){.x = 49 + 1 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[(health / 10) % 10], NULL,
														hud->scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = 49 + 2 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[health % 10], NULL, hud->scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = 49 + 3 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[10], NULL, hud->scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = 104, .y = 0};
		SDL_BlitSurface(hud->arms, NULL, hud->scr, &hud->rect);
		i = 1;
		while (++i < 7)
		{
			if (i < 5)
				hud->rect = (SDL_Rect){.x = 111 + (i - 2) * 12, .y = 4};
			else
				hud->rect = (SDL_Rect){.x = 111 + (i - 5) * 12, .y = 14};
			if (weapon & (1 << (i - 1)))
				SDL_BlitSurface(hud->num_wp_y[i], NULL, hud->scr, &hud->rect);
			else
				SDL_BlitSurface(hud->num_wp_g[i], NULL, hud->scr, &hud->rect);
		}
		hud->rect = (SDL_Rect){.x = 148, .y = 2};
		SDL_BlitSurface(hud->face_s[2], NULL, hud->scr, &hud->rect);
		coef = scr->w / hud->hud->w;
		hud->rect = (SDL_Rect){.x = 0, .y = scr->h - scr->w / 10,
												.w = scr->w, .h = scr->w / 10};
		SDL_BlitScaled(hud->scr, NULL, scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = (scr->w - hud->pis[b]->w * coef) >> 1,
					.y = scr->h - hud->hud->h * coef - hud->pis[b]->h * coef,
						.w = hud->pis[b]->w * coef, .h = hud->pis[b]->h * coef};
		SDL_BlitScaled(hud->pis[b], NULL, scr, &hud->rect);
	}
}

int				main(int argc, char const *argv[])
{
	t_engine	engine;

	engine = (t_engine){.w = 1920, .h = 1080};
	if (init_engine(&engine) != 0)
		return (1);
	put_hud(engine.screen, 98, 0b11010, 0);
	SDL_UpdateWindowSurface(engine.window);
	while (!engine.close_request)
	{
		while (SDL_PollEvent(&engine.player.event))
			if (engine.player.event.type == SDL_KEYDOWN
									|| engine.player.event.type == SDL_KEYUP)
			{
				if (engine.player.event.key.keysym.sym == SDLK_LCTRL)
					engine.player.eyeheight = EyeHeight -
						(engine.player.event.type == SDL_KEYDOWN) * DuckHeight;
				else if (engine.player.event.key.keysym.sym == SDLK_ESCAPE)
					engine.close_request = 1;
			}
			else if (engine.player.event.type == SDL_QUIT)
				engine.close_request = 1;
		SDL_UpdateWindowSurface(engine.window);
	}
	return (0);
}
