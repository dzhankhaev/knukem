/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:44:33 by ecelsa            #+#    #+#             */
/*   Updated: 2021/02/08 22:46:39 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "editor.h"
#include "utilits.h"

void		hud_load_stysnum(t_hud *hud, char *file_name, int len)
{
	int		i;

	i = -1;
	ft_strcpy(file_name + len, "STYSNUM .png");
	while (++i < 10)
	{
		file_name[len + 7] = i + '0';
		if (!(hud->num_wp_y[i] = IMG_Load(file_name)))
			exc(__FILE__, __FUNCTION__);
	}
}

int			load_hud_face_pis_yenum(t_hud *hud, char *file_name, int len, int i)
{
	ft_strcpy(file_name + len, "STFST00.png");
	if (!(hud->face_s[0] = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	ft_strcpy(file_name + len, "STFST01.png");
	if (!(hud->face_s[1] = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	ft_strcpy(file_name + len, "STFST02.png");
	if (!(hud->face_s[2] = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	ft_strcpy(file_name + len, "PISGA0.png");
	while (++i < 5)
	{
		file_name[len + 4] = 'A' + i;
		if (!(hud->pis[i] = IMG_Load(file_name)))
			exc(__FILE__, __FUNCTION__);
	}
	ft_strcpy(file_name + len, "PISFA0.png");
	if (!(hud->pis[5] = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	ft_strcpy(file_name + len, "STYSNUM .png");
	hud_load_stysnum(hud, file_name, len);
	return (1);
}

int			load_hud_hnum_gnum(t_hud *hud, char *file_name, int len, int i)
{
	ft_strcpy(file_name + len, "STGNUM .png");
	while (++i < 11)
	{
		if (i < 10)
		{
			file_name[len + 2] = 'G';
			file_name[len + 6] = i + '0';
			if (!(hud->num_wp_g[i] = IMG_Load(file_name)))
				exc(__FILE__, __FUNCTION__);
			file_name[len + 2] = 'T';
		}
		else
			ft_strcpy(file_name + len, "STTPRCNT.png");
		if (!(hud->num_h[i] = IMG_Load(file_name)))
			exc(__FILE__, __FUNCTION__);
	}
	return (1);
}

int			hud_check_next_frame(int *b, t_hud *hud, t_inp_hud *inp)
{
	static unsigned int		last_tick = 0;
	unsigned int			curr_tick;

	if (last_tick == 0)
		last_tick = SDL_GetTicks();
	curr_tick = SDL_GetTicks();
	if (curr_tick > (last_tick + 100))
	{
		last_tick = curr_tick;
		if (inp->fire && *b < 3)
			(*b)++;
		else
		{
			inp->fire = 0;
			(*b) = 0;
		}
	}
	return (1);
}

void		load_surfaces(const char *dirs, t_hud *hud_)
{
	t_hud	hud;
	char	*file_name;
	int		len;

	ft_memset(&hud, 0xff, sizeof(t_hud));
	len = ft_strlen(dirs);
	file_name = (char*)malloc(len + 13);
	ft_strcpy(file_name, dirs);
	ft_strcpy(file_name + len, "STBAR.png");
	if (!(hud.hud = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	ft_strcpy(file_name + len, "ammo_b.png");
	if (!(hud.ammo_b = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	ft_strcpy(file_name + len, "STARMS.png");
	if (!(hud.arms = IMG_Load(file_name)))
		exc(__FILE__, __FUNCTION__);
	hud.scr = SDL_CreateRGBSurface(0, 320, 32, 32,
											0xff0000, 0xff00, 0xff, 0xff000000);
	SDL_BlitSurface(hud.hud, NULL, hud.scr, NULL);
	load_hud_face_pis_yenum(&hud, file_name, len, -1);
	load_hud_hnum_gnum(&hud, file_name, len, -1);
	free(file_name);
	*hud_ = hud;
}