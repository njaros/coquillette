/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:01:14 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/21 15:42:22 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lsttake(t_list **alst)
{
	t_list	*token;

	if (!*alst)
		return (NULL);
	token = *alst;
	*alst = (*alst)->next;
	token->next = NULL;
	return (token);
}
