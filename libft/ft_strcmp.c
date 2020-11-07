/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:10:10 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 23:01:21 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *p1, const char *p2)
{
	unsigned char	*s1;
	unsigned char	*s2;
	int				a;

	s1 = (unsigned char *)p1;
	s2 = (unsigned char *)p2;
	a = 0;
	while (s1[a] != '\0' && s2[a] != '\0' && s1[a] == s2[a])
		++a;
	return (s1[a] - s2[a]);
}
