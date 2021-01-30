/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:47 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		button_pressed(int i, t_button *buttons)
{
	while (i < BUTTONS)
	{
		if (buttons[i].state)
			break ;
		i++;
	}
	return (i);
}

void	apply_changes(t_all *all, t_button *btn, int i)
{
	t_xy	*temp;

	i = button_pressed(i, btn);
	temp = i < 14 ? &all->draw_floors : &all->set_floors;
	if ((i - 2 == 0 || i - 14 == 0) && temp->x > 0)
		temp->x -= 1;
	else if ((i - 2 == 1 || i - 14 == 1) && temp->y < 200)
	{
		temp->y += temp->x == temp->y ? 1 : 0;
		temp->x += 1;
	}
	else if ((i - 2 == 2 || i - 14 == 2) && temp->y > 0)
	{
		temp->x -= temp->y == temp->x ? 1 : 0;
		temp->y -= 1;
	}
	else if ((i - 2 == 3 || i - 14 == 3) && temp->y < 200)
		temp->y += 1;
}

void	sector_change(t_all *all, t_sect *sectors, int num)
{
	int i;

	i = button_pressed(14, all->buttons);
	if (i - 14 == 0 && sectors[num].floor > 0)
		sectors[num].oldf = sectors[num].floor -= 1;
	else if (i - 14 == 1 && sectors[num].floor < 200)
	{
		sectors[num].ceil += sectors[num].floor == sectors[num].ceil ? 1 : 0;
		sectors[num].oldf = sectors[num].floor += 1;
	}
	else if (i - 14 == 2 && sectors[num].ceil > 0)
	{
		sectors[num].oldf = sectors[num].floor -=\
			(sectors[num].floor == sectors[num].ceil ? 1 : 0);
		sectors[num].ceil -= 1;
	}
	else if (i - 14 == 3 && sectors[num].ceil < 200)
		sectors[num].ceil += 1;
	if (sectors[num].ceil - sectors[num].floor < 6)
		all->player.sector = -1;
}

void	game_setting_values(t_settings *set, t_button *btns)
{
	int i;

	i = button_pressed(6, btns);
	if (i == 6 && set->inventory > 1)
		set->inventory--;
	else if (i == 7 && set->inventory < 9)
		set->inventory++;
	else if (i == 8 && set->speed > 10)
		set->speed -= 10;
	else if (i == 9 && set->speed < 100)
		set->speed += 10;
	else if (i == 10 && set->gravity > 10)
		set->gravity -= 10;
	else if (i == 11 && set->gravity < 100)
		set->gravity += 10;
	else if (i == 12 && set->ammo > 0)
		set->ammo -= 1;
	else if (i == 13 && set->ammo < 30)
		set->ammo += 1;
}

void	processing(t_all *all)
{
	if (all->swap_num == -1)
	{
		apply_changes(all, all->buttons, 2);
		game_setting_values(&all->player.settings, all->buttons);
	}
	else
		sector_change(all, all->sectors, all->swap_num);
}
