/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:26:26 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:26:30 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *block, int c, size_t n)
{
	size_t				i;
	unsigned const char	*check;

	check = block;
	i = 0;
	while (i < n)
	{
		if (check[i] == (unsigned char) c)
			return ((unsigned char *) &check[i]);
		i++;
	}
	return (0);
}
