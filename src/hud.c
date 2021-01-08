/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:47:49 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/17 12:32:48 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "libft.h"

typedef struct	s_hud
{
	SDL_Surface		*scr;
	SDL_Rect		rect;
	int				health;
	int				weapon;
	int				face;
	SDL_Surface		*hud;
	SDL_Surface		*arms;
	SDL_Surface		*pis[6];
	SDL_Surface		*num_h[11];
	SDL_Surface		*num_wp_g[10];
	SDL_Surface		*num_wp_y[10];
	SDL_Surface		*face_s[3];
}				t_hud;

typedef struct	s_inp_hud
{
	int				health;
	int				weapons;
	int				curr_weap;
	int				ammo[6];
	int				face;
	int				fire;
	int 			flag;
}				t_inp_hud;


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

	hud = (t_hud*)malloc(sizeof(t_hud));	
	hud->health = -1;
	hud->weapon = -1;
	hud->face = -1;
	len = ft_strlen(dirs);
	file_name = (char*)malloc(len + 13);
	ft_strcpy(file_name, dirs);
	ft_strcpy(file_name + len, "STBAR.png");
	hud->hud = IMG_Load(file_name);
	ft_strcpy(file_name + len, "STARMS.png");
	hud->arms = IMG_Load(file_name);
	hud->scr = SDL_CreateRGBSurface(0, 320, 32, 32,
											0xff0000, 0xff00, 0xff, 0xff000000);
	SDL_BlitSurface(hud->hud, NULL, hud->scr, NULL);
	load_hud_face_pis_yenum(hud, file_name, len, -1);
	load_hud_hnum_gnum(hud, file_name, len, -1);
	free(file_name);
	return (hud);
}

void			put_hud(SDL_Surface *scr, t_inp_hud *inp)
{
	static t_hud			*hud = NULL;
	static unsigned int		last_tick = 0;
	unsigned int			curr_tick;
	static int				b = 0;
	int						i;
	int						coef;

	if (hud == NULL)
		hud = load_surfaces("textur/");
	if (last_tick == 0)
		last_tick = SDL_GetTicks();
	curr_tick = SDL_GetTicks();

	if (curr_tick > (last_tick + 100))
	{
		last_tick = curr_tick;
		if (inp->fire && b < 2)
			b++;
		else
		{
			inp->fire = 0;
			b = 0;
		}
	}
	// if (inp->health != hud->health || inp->weapons != hud->weapon || inp->face != hud->face || inp->fire)
	{
		ft_bzero(scr->pixels,scr->pitch * scr->h);
		hud->health = inp->health;
		hud->weapon = inp->weapons;
		hud->face = inp->face;
		SDL_BlitSurface(hud->scr, NULL, hud->hud, NULL);
		if (inp->health / 100 > 0)
		{
			hud->rect = (SDL_Rect){.x = 49 + 0 * 14, .y = 4};
			SDL_BlitSurface(hud->num_h[inp->health / 100], NULL, hud->scr, &hud->rect);
		}
		hud->rect = (SDL_Rect){.x = 49 + 1 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[(inp->health / 10) % 10], NULL,
														hud->scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = 49 + 2 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[inp->health % 10], NULL, hud->scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = 49 + 3 * 14, .y = 4};
		SDL_BlitSurface(hud->num_h[10], NULL, hud->scr, &hud->rect);
		hud->rect = (SDL_Rect){.x = 104, .y = 0};
		SDL_BlitSurface(hud->arms, NULL, hud->scr, &hud->rect);
		i = 1;
		while (++i < 8)
		{
			if (i < 5)
				hud->rect = (SDL_Rect){.x = 111 + (i - 2) * 12, .y = 4};
			else
				hud->rect = (SDL_Rect){.x = 111 + (i - 5) * 12, .y = 14};
			if (inp->weapons & (1 << (i - 1)))
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
					.y = scr->h - scr->w / 10 - hud->pis[b]->h * coef,
						.w = hud->pis[b]->w * coef, .h = hud->pis[b]->h * coef};
		SDL_BlitScaled(hud->pis[b], NULL, scr, &hud->rect);
		if (b == 1)
		{
			hud->rect = (SDL_Rect){.x = ((scr->w - (hud->pis[b]->w - 72) * coef) >> 1),
					.y = scr->h - scr->w / 10 - (hud->pis[b]->h + 21) * coef,
						.w = hud->pis[5]->w * coef, .h = hud->pis[5]->h * coef};
			SDL_BlitScaled(hud->pis[5], NULL, scr, &hud->rect);
		}
	}
}

int				main(int argc, char const **argv)
{
	t_engine	engine;
	t_inp_hud	input_hud;

	input_hud = (t_inp_hud){.weapons = 0b11101, .health = 125, .face = 1, .flag = 0, .fire = 0};
	engine = (t_engine){.w = 800, .h = 500};
	if (init_engine(&engine) != 0)
		return (1);
	put_hud(engine.screen, &input_hud);
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
				else if (engine.player.event.key.keysym.sym == SDLK_SPACE)
				{
					input_hud.fire = 1;
					write(1,"space\n",6);
				}
			}
			else if (engine.player.event.type == SDL_QUIT)
				engine.close_request = 1;
		
		put_hud(engine.screen, &input_hud);
		SDL_UpdateWindowSurface(engine.window);
	}
	return (0);
}
