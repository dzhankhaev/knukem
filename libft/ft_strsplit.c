/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:41:18 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 21:11:36 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	wc(char const *s, char c)
{
	int k;

	k = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c)
		{
			k++;
			while (*s != c && *s)
				s++;
		}
	}
	return (k);
}

static int	wl(const char *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		k;

	if (!s || !(str = (char**)malloc(sizeof(char*) * (wc((char*)s, c) + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!(str[i] = (char*)malloc(sizeof(char) * (wl((char*)s, c) + 1))))
				return (NULL);
			while (*s != c && *s)
				str[i][k++] = (char)*s++;
			str[i][k] = '\0';
			i++;
			k = 0;
		}
		while (*s && *s == c)
			s++;
	}
	str[i] = NULL;
	return (str);
}
