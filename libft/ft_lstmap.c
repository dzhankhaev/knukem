/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:30:02 by sisidra           #+#    #+#             */
/*   Updated: 2019/10/25 22:05:04 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *iter;
	t_list *res;
	t_list *temp;

	if (!(lst || f))
		return (NULL);
	temp = f(lst);
	if ((res = ft_lstnew(temp->content, temp->content_size)))
	{
		iter = res;
		lst = lst->next;
		while (lst)
		{
			temp = (*f)(lst);
			if (!(iter->next = ft_lstnew(temp->content,
					temp->content_size)))
				return (NULL);
			iter = iter->next;
			lst = lst->next;
		}
	}
	return (res);
}
