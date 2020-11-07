/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:31:54 by sisidra           #+#    #+#             */
/*   Updated: 2020/08/10 18:31:54 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	c_arg(t_complex a)
{
	double	arg;
	double	pi;

	pi = 3.1415926535;
	if (a.re < 0 && a.im > 0)
		arg = pi + atan(a.im / a.re);
	else if (a.re < 0 && a.im < 0)
		arg = -pi + atan(a.im / a.re);
	else
		arg = atan(a.im / a.re);
	return (arg);
}
