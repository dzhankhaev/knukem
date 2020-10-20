/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:32:34 by ecelsa            #+#    #+#             */
/*   Updated: 2020/10/20 15:46:13 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_wad.h"


void			pars_colum(SDL_Surface *scr, t_patch *patch, unsigned char *clp)
{
	t_pars_colum sub;

	sub.x = -1;
	while (++sub.x < patch->width)
	{
		sub.size = (sub.x != patch->width - 1) ? patch->columnofs[sub.x + 1] -
		patch->columnofs[sub.x] : patch->size_patch - patch->columnofs[sub.x];
		sub.i = -1;
		while (++sub.i < sub.size - 1)
		{
			sub.pixel = ((int*)scr->pixels + sub.x)
										+ (scr->w * patch->colum[sub.x][sub.i]);
			sub.col = patch->colum[sub.x][sub.i + 1];
			sub.i += 3;
			while (sub.col--)
			{
				sub.index = patch->colum[sub.x][sub.i] * 3;
				*sub.pixel = AMASK | (clp[sub.index] << 16)
							| (clp[sub.index + 1] << 8) | clp[sub.index + 2];
				sub.pixel += patch->width;
				sub.i++;
			}
		}
	}
}

t_patch			*init_patch(t_wad *wad)
{
	t_patch	*patch;

	if ((patch = (t_patch*)malloc(sizeof(t_patch))))
	{
		patch->size_patch = wad->dir.size;
		if ((patch->mem = (unsigned char*)malloc(sizeof(char) * wad->dir.size)))
		{
			patch->type = -1;
			patch->colum = NULL;
			patch->columnofs = NULL;
			patch->surface = NULL;
			ft_strcpy(patch->name, wad->dir.name);
			return (patch);
		}
		else
		{
			free(patch);
			return (NULL);
		}
	}
	return (NULL);
}

void			free_patch(t_patch **patch)
{
	int	i;

	i = -1;
	if (*patch)
	{
		if ((*patch)->colum)
		{
			while (++i < (*patch)->width)
				free((*patch)->colum[i]);
			free((*patch)->colum);
		}
		if ((*patch)->columnofs)
			free((*patch)->columnofs);
		if ((*patch)->surface)
			free((*patch)->surface);
		if ((*patch)->mem)
			free((*patch)->mem);
		free((*patch));
	}
	*patch = NULL;
}

void			fill_patch_columos(t_patch *patch)
{
	int		i;
	int		size;

	i = 0;
	patch->columnofs = (int*)malloc(sizeof(int) * patch->width);
	ft_memcpy(patch->columnofs, patch->mem + 8, patch->width * sizeof(int));
	patch->colum = (unsigned char**)malloc(sizeof(char*) * patch->width);
	i = -1;
	while (++i < patch->width)
	{
		size = (i != patch->width - 1) ? patch->columnofs[i + 1] -
				patch->columnofs[i] : patch->size_patch - patch->columnofs[i];
		patch->colum[i] = (unsigned char*)malloc(size);
		ft_memcpy(patch->colum[i], patch->mem + patch->columnofs[i], size);
	}
}

void			pars_patch(t_patch *patch)
{
	if (patch)
	{
		ft_memcpy(patch, patch->mem, 8);
		if (patch->width > 640 || patch->width == 0
								|| patch->height > 640 || patch->height == 0)
			patch->type = 1;
		else
		{
			patch->type = 0;
			fill_patch_columos(patch);
		}
	}
}

t_patch			*load_patch(char *name_file, char *name_dir)
{
	t_wad		wad;
	t_patch		*patch;

	wad.fr = 1;
	if ((wad.fd = open(name_file, O_RDONLY)))
	{
		read(wad.fd, (void*)&wad, 12);
		lseek(wad.fd, wad.mem_start, 0);
		while (ft_memcmp(name_dir, wad.dir.name, ft_strlen(name_dir)) && wad.fr)
			wad.fr = read(wad.fd, (void*)&wad.dir, 16);
		if (!(ft_memcmp(name_dir, wad.dir.name, ft_strlen(name_dir))))
		{
			lseek(wad.fd, wad.dir.filepos, 0);
			if ((patch = init_patch(&wad)))
			{
				read(wad.fd, (void*)patch->mem, wad.dir.size);
				pars_patch(patch);
			}
			close(wad.fd);
			return (patch);
		}
		else
			close(wad.fd);
	}
	return (NULL);
}

SDL_Surface		*patch(t_patch *patch)
{
	return (patch->surface);
}

void			put_patch_on_scr(char *name_patch, SDL_Surface *dst_scr,
										SDL_Rect *rect, unsigned char* colormap)
{
	t_patch		*patch;
	SDL_Surface	*scr;

	if ((patch = load_patch("Doom1.WAD", name_patch)))
		{
			scr = SDL_CreateRGBSurface(0, patch->width, patch->height,
												32, RMASK, GMASK, BMASK, AMASK);
			pars_colum(scr, patch, colormap);
			SDL_BlitSurface(scr, NULL, dst_scr, rect);
			free_patch(&patch);
		}
		SDL_FreeSurface(scr);
}

SDL_Surface		*hud(int hp, char armors, SDL_Surface *scr, unsigned char* colormap)
{
	char		ch_num[4][8];
	char		st[8];
	int			i;
	SDL_Rect	rr;

	ft_bzero(&ch_num, 4*8);
	i = -1;
	ft_strcpy(ch_num[0],"STTNUM");
	ch_num[0][6] = hp / 100 + '0';
	ft_strcpy(ch_num[1],"STTNUM");
	ch_num[1][6] = (hp / 10) % 10 + '0' ;
	ft_strcpy(ch_num[2],"STTNUM");
	ch_num[2][6] = hp % 10 + '0';
	ft_strcpy(ch_num[3],"STTPRCNT");
	i = -1;
	while (++i < 4)
	{
		rr = (SDL_Rect){.x = 49 + i * 14, .y = 4};
		if (!(i == 0 && (hp / 100) == 0))
			put_patch_on_scr(ch_num[i], scr, &rr, colormap);
	}
	rr = (SDL_Rect){.x = 104, .y = 0};
	put_patch_on_scr("STARMS", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 111, .y = 4};
	if (armors & 0b10)
		put_patch_on_scr("STYSNUM2", scr, &rr, colormap);
	else
		put_patch_on_scr("STGNUM2", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 123, .y = 4};
	if (armors & 0b100)
		put_patch_on_scr("STYSNUM3", scr, &rr, colormap);
	else
		put_patch_on_scr("STGNUM3", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 135, .y = 4};
	if (armors & 0b1000)
		put_patch_on_scr("STYSNUM4", scr, &rr, colormap);
	else
		put_patch_on_scr("STGNUM4", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 111, .y = 14};
	if (armors & 0b10000)
		put_patch_on_scr("STYSNUM5", scr, &rr, colormap);
	else
		put_patch_on_scr("STGNUM5", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 123, .y = 14};
	if (armors & 0b100000)
		put_patch_on_scr("STYSNUM6", scr, &rr, colormap);
	else
		put_patch_on_scr("STGNUM6", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 135, .y = 14};
	if (armors & 0b1000000)
		put_patch_on_scr("STYSNUM7", scr, &rr, colormap);
	else
		put_patch_on_scr("STGNUM7", scr, &rr, colormap);
	rr = (SDL_Rect){.x = 148, .y = 2};
	put_patch_on_scr("STFTR00", scr, &rr, colormap);
	return(NULL);
}

int				main(int argc, char **argv)
{
	t_engine	engine;
	char		*mem;
	t_wad		wad;
	SDL_Surface	*lmp;
	t_patch		*patch;
	char		colormap[14][256 * 3];
	int			pow;
	int			pal = 10;

	if (argc == 1)
	{
		write(1, "No patch Name\n", 14);
		return(0);
	}
	lmp = NULL;
	patch = load_patch("Doom1.WAD", "PLAYPAL");
	ft_memcpy(colormap, patch->mem, patch->size_patch);
	free_patch(&patch);
	if ((patch = load_patch("Doom1.WAD", argv[1])))
	{	
		lmp = SDL_CreateRGBSurface(0, patch->width, patch->height,
											32, RMASK, GMASK, BMASK, AMASK);
		pars_colum(lmp, patch, (unsigned char*)colormap[pal]);
	}
	if (lmp)
	{	
		if (lmp->w > lmp->h)
			pow = 1920 / lmp->w;
		else
			pow = 1080 / lmp->h;
		engine = (t_engine){.w = lmp->w * pow, .h = lmp->h * pow};
	}
	else
		engine = (t_engine){.w = 400, .h = 600};
	free_patch(&patch);
	hud(358,0b00110, lmp, (unsigned char*)colormap[pal]);
	if (init_engine(&engine) != 0)
		return (1);
	SDL_BlitScaled(lmp, NULL, engine.screen, NULL);
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
			// SDL_UpdateWindowSurface(engine.window);
	}
	return (0);
}
