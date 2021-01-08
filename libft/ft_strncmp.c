/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:51:13 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 23:01:56 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *p1, const char *p2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			a;

	s1 = (unsigned char *)p1;
	s2 = (unsigned char *)p2;
	if (n == 0)
		return (0);
	a = 0;
	while (s1[a] != '\0' && s2[a] != '\0' && s1[a] == s2[a] && a < n)
	{
		a++;
		if (a == n && s1[a] != s2[a])
			return (s1[a - 1] - s2[a - 1]);
	}
	return (s1[a] - s2[a]);
}
