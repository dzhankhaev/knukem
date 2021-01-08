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
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:13:01 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		wcounter(char const *s, char c)
{
	int	i;
	int word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			word++;
		i++;
	}
	return (word);
}

static int		wlencounter(char const *s, char c, int i)
{
	int j;

	j = 0;
	while (s[i] != c && s[i])
	{
		j++;
		i++;
	}
	return (j);
}

static int		tomake25lines(int i, char **res, char const *s, char c)
{
	int k;

	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(res[k] = ft_strsub(s, i, wlencounter(s, c, i))))
			{
				while (k)
				{
					free(res[k]);
					k--;
				}
				break ;
			}
			k++;
			i += wlencounter(s, c, i);
		}
		else
			i++;
	}
	return (k);
}

char			**ft_strsplit(char const *s, char c)
{
	int					k;
	char				**res;
	unsigned int		i;

	i = 0;
	if (!s || !(res = (char**)malloc(sizeof(char**) * (wcounter(s, c) + 1))))
		return (NULL);
	k = tomake25lines(i, res, s, c);
	if (!k && wcounter(s, c))
	{
		free(res);
		return (NULL);
	}
	res[k] = NULL;
	return (res);
}
>>>>>>> master
