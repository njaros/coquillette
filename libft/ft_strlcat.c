/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:31:11 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:31:16 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	k = i;
	while (src[j] != '\0')
		j++;
	if (k >= size)
		return (size + j);
	while ((i < size - 1) && (*src != '\0'))
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return (k + j);
}
