/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reorder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:55:57 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/07 09:56:16 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	reorder_lst(t_list **lst, t_list *prev)
{
	t_list	*temp;

	temp = *lst;
	if (prev)
		prev->next = (*lst)->next;
	*lst = (*lst)->next;
	ft_lstdelone(temp, free);
}
