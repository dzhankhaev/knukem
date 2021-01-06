/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:14:36 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/28 17:18:11 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *srch, size_t len)
{
	unsigned int	f;
	unsigned int	i;

	if (*srch == 0)
		return ((char*)str);
	f = 0;
	while (str[f] != '\0' && (size_t)f < len)
	{
		i = 0;
		if (str[f] == srch[i])
		{
			i++;
			while (srch[i] != '\0' && str[f + i] == srch[i] &&
											(size_t)(f + i) < len)
				++i;
			if (srch[i] == '\0')
				return ((char*)&str[f]);
		}
		++f;
	}
	return (0);
}
