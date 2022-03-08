/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:33:21 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:33:26 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	secure;
	size_t	i;

	i = 0;
	secure = 1;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		secure = 0;
		start = ft_strlen(s);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub = malloc(sizeof(char) * secure * len + 1);
	if (!sub)
		return (NULL);
	while ((i < len) && (s[start + i]))
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
