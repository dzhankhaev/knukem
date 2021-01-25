/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ispointincube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

int	ispointincube(t_xyz point, t_xyz cubecenter, t_xyz borders,
				float centerzoffset)
{
	return (((cubecenter.x + borders.x > point.x) &
		(point.x > cubecenter.x - borders.x)) &&
		((cubecenter.y + borders.y > point.y) &
		(point.y > cubecenter.y - borders.y)) &&
		((cubecenter.z + centerzoffset + borders.z > point.z) &
		(point.z > cubecenter.z + centerzoffset - borders.z)));
}
