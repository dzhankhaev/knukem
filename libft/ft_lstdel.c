/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:27:25 by sisidra           #+#    #+#             */
/*   Updated: 2019/10/25 21:45:56 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *tmptmp;

	tmp = *alst;
	while (tmp)
	{
		tmptmp = tmp;
		ft_lstdelone(&tmp, del);
		tmp = tmptmp->next;
	}
	*alst = NULL;
}
