/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:30:54 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:30:58 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*join;

	if ((s1 == NULL) && (s2 == NULL))
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (l1 + l2) + 1);
	if (!join)
		return (NULL);
	while (s1 && i < l1)
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && i < l1 + l2)
	{
		join[i] = s2[i - l1];
		i++;
	}
	join[i] = '\0';
	return (join);
}
