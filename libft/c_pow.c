/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_pow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:09:23 by sisidra           #+#    #+#             */
/*   Updated: 2020/08/10 18:09:23 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex	c_pow(t_complex a, int n)
{
	t_complex	res;
	double		arg;
	double		mod;

	arg = c_arg(a);
	mod = c_mod(a);
	res.re = pow(mod, n) * cos(arg * n);
	res.im = pow(mod, n) * sin(arg * n);
	return (res);
}
