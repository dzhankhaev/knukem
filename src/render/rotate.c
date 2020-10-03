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

t_xy	rot_z(t_xy p, float angle)
{
	float x;
	float y;

	x = p.x;
	y = p.y;
	p.x = x * cosf(angle) - y * sinf(angle);
	p.y = x * sinf(angle) + y * cosf(angle);
	return (p);
}
