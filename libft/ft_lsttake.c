/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:01:14 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/07 10:01:39 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lsttake(t_list **alst)
{
	t_list	*token;

	if (!*alst)
		return NULL;
	token = *alst;
	*alst = (*alst)->next;
	token->next = NULL;
	return (token);
}
