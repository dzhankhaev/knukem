/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:53:00 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*res;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	i = 0;
	size = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (size >= 0 && (s[size] == ' ' || s[size] == '\n' || s[size] == '\t'))
		size--;
	if ((size >= i) && (res = ft_strsub(s, i, size - i + 1)))
		return (res);
	return (ft_strnew(0));
}
