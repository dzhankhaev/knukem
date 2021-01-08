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
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:23:48 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1[0] == '\0' && s2[0] == '\0')
		return (0);
	return (ft_memcmp(s1, s2, ft_strlen(s1) < ft_strlen(s2) ? ft_strlen(s2) :
			ft_strlen(s1)));
}
>>>>>>> master
