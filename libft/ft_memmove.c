/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:27:04 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:27:06 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*fill;
	const char	*check;
	size_t		i;

	if (!dest && !src)
		return (dest);
	i = 0;
	fill = dest;
	check = src;
	if (fill <= check)
	{
		while (i < n)
		{
			fill[i] = check[i];
			i++;
		}
		n = 0;
	}
	while (n > 0)
	{
		fill[n - 1] = check[n - 1];
		n--;
	}
	return (dest);
}
