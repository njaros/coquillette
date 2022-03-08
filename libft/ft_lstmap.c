/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:25:27 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:25:31 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*secure;
	void	*data;

	map = NULL;
	while (lst != NULL)
	{
		data = (*f)(lst->content);
		secure = ft_lstnew(data);
		if (secure == NULL)
			ft_lstclear(&map, (*del));
		else
			ft_lstadd_back(&map, secure);
		lst = lst->next;
	}
	return (map);
}
