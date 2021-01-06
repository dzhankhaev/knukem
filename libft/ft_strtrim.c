/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:11:31 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/30 19:43:12 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	countspaces(char const *s, int n)
{
	int i;
	int j;

	i = 0;
	if (n == 1)
	{
		j = 0;
		i = ft_strlen((char*)s);
		while ((i > 0) && (s[i - 1] == ' ' || s[i - 1] == '\n' ||
					s[i - 1] == '\t'))
		{
			i--;
			j++;
		}
		return (j);
	}
	if (n == 0)
	{
		while (s && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i++;
		return (i);
	}
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		c;
	int		len;
	char	*str;

	if (s)
	{
		len = ft_strlen((char*)s);
		if (len == 0 || len == countspaces(s, 1))
			return (ft_strdup(""));
		i = (countspaces(s, 1) + countspaces(s, 0));
		if (!(str = (char*)malloc(sizeof(char) * (len - i + 1))))
			return (NULL);
		c = 0;
		i = countspaces(s, 0);
		while (i < (len - countspaces(s, 1)))
		{
			str[c] = s[i];
			c++;
			i++;
		}
		str[c] = '\0';
		return (str);
	}
	return (NULL);
}
