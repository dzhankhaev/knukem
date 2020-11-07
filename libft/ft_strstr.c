/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:51:24 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/28 22:17:53 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *srch)
{
	unsigned int	i;
	unsigned int	f;

	if (*srch == 0)
		return ((char*)str);
	f = 0;
	i = 0;
	while (str[f] != '\0')
	{
		if (str[f] == srch[i])
		{
			while (str[f + i] == srch[i] && srch[i] != '\0')
				i++;
			if (srch[i] == '\0')
				return ((char*)&str[f]);
			else
				i = 0;
		}
		f++;
	}
	return (NULL);
}
