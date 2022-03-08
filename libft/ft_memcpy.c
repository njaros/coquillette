/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:26:51 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:26:53 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	char				*fill;
	unsigned const char	*check;

	if ((dest == NULL) && (src == NULL))
		return (dest);
	i = 0;
	fill = dest;
	check = src;
	while (i < n)
	{
		fill[i] = check[i];
		i++;
	}
	return (dest);
}
