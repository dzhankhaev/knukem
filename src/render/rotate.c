/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:05:54 by abeulah           #+#    #+#             */
/*   Updated: 2020/02/25 14:10:29 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_xy	rot_z(t_xy p, double angle)
{
	int x;
	int y;

	x = p.x;
	y = p.y;
	p.x = x * cos(angle) - y * sin(angle);
	p.y = x * sin(angle) + y * cos(angle);
	return (p);
}
