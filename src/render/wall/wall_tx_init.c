/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tx_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

t_line		get_op1(t_temp *a)
{
	return ((t_line){0, 0, a->oy[0],
				imin(a->oy[2], a->oy[1]), 0});
}

t_line		get_op2(t_temp *a)
{
	return ((t_line){0, 0, a->oy[3],
				a->oy[1], 0});
}

t_line		get_op3(t_temp *a)
{
	return ((t_line){0, 0, a->oy[0], a->oy[1], 0});
}
