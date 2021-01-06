/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:19:51 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/28 16:22:01 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = ft_strlen((char*)s);
	if (c == '\0')
		return ((char*)&s[i]);
	while (i >= 0)
	{
		if (s[i] == c)
			return (char*)&s[i];
		i--;
	}
	return (NULL);
}
