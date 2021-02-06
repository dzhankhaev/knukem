/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_one_graf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	copy_graf(t_graf *graf, int t, t_graf *graf2)
{
	int q;
	int	k;

	q = 0;
	k = 0;
	while (k < graf->g_num + 1)
	{
		if (k == t)
		{
			k++;
			continue;
		}
		graf2->coord[q] = graf->coord[k];
		graf2->z[q] = graf->z[k];
		graf2->wall[q] = graf->wall[k];
		q++;
		k++;
	}
}

void		delete_one_graf(t_engine *engine, int sectorno)
{
	t_graf	*graf;
	t_graf	graf2;

	graf = &engine->sectors[sectorno].graf;
	graf->g_num--;
	graf2.coord = (t_fline *)malloc(sizeof(t_fline) * graf->g_num);
	graf2.z = (float *)malloc(sizeof(float) * graf->g_num);
	graf2.wall = (int *)malloc(sizeof(int) * graf->g_num);
	graf2.u = (int *)malloc(sizeof(int) * graf->g_num);
	copy_graf(graf, engine->edit.graf_wall, &graf2);
	free(graf->coord);
	free(graf->z);
	free(graf->wall);
	free(graf->u);
	graf->coord = graf2.coord;
	graf->z = graf2.z;
	graf->wall = graf2.wall;
	graf->u = graf2.u;
	engine->edit.graf_wall = -1;
}
