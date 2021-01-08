/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:31:22 by sisidra           #+#    #+#             */
/*   Updated: 2019/10/25 21:44:12 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = (void*)malloc(sizeof(content) * content_size)))
			return (NULL);
		ft_memcpy(new->content, content, (sizeof(content) * content_size));
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:12:55 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;
	void	*dup_content;
	size_t	dup_content_size;

	if (!(res = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		dup_content = ft_memalloc(content_size);
		dup_content_size = content_size;
		ft_memcpy(dup_content, content, content_size);
		res->content = dup_content;
		res->content_size = dup_content_size;
	}
	res->next = NULL;
	return (res);
}
>>>>>>> master
