/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:39:49 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 20:22:06 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (s && f)
	{
		str = ft_strnew(ft_strlen((char*)s));
		if (str == NULL)
			return (NULL);
		i = 0;
		while (s[i] != '\0')
		{
			str[i] = f(i, s[i]);
			i++;
		}
		return (str);
	}
	return (NULL);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:14:22 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	i = 0;
	if (!s || !(res = ft_memalloc((size_t)ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
>>>>>>> master
