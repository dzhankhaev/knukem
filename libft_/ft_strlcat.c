/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:46:29 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	int		i;
	size_t	lensrc;
	size_t	lendst;

	i = 0;
	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (lendst >= n)
		lensrc = lensrc + n;
	else
		lensrc = lensrc + lendst;
	while (src[i] && (lendst + 1 < n))
	{
		dst[lendst] = src[i];
		lendst++;
		i++;
	}
	dst[lendst] = '\0';
	return (lensrc);
}
