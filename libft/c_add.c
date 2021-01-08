/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:07:25 by sisidra           #+#    #+#             */
/*   Updated: 2020/08/10 18:07:25 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex	c_add(t_complex a, t_complex b)
{
	t_complex c;

	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return (c);
}
