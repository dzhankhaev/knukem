/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:35:46 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/28 21:12:27 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long int	i;
	unsigned char		*refdst;
	unsigned char		*refsrc;

	if (dst == NULL && src == NULL && len)
		return (NULL);
	refdst = (unsigned char*)dst;
	refsrc = (unsigned char*)src;
	i = 0;
	if (refdst < refsrc)
	{
		while (i < len)
		{
			refdst[i] = refsrc[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			refdst[len] = refsrc[len];
	}
	return (refdst);
}
