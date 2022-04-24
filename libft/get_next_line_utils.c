/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:42:16 by njaros            #+#    #+#             */
/*   Updated: 2021/11/20 10:42:16 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = -1;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		free(s);
		return (NULL);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while ((++i < len) && (s[start + i]))
		sub[i] = s[start + i];
	sub[i] = '\0';
	free(s);
	return (sub);
}

char	*ft_strjoin_free(char *s1, char *s2, int del)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*join;

	if (s2 == NULL)
		return (s1);
	i = -1;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (l1 + l2) + 1);
	if (!join)
		return (NULL);
	while (++i < l1)
		join[i] = s1[i];
	i--;
	while (++i < l1 + l2)
		join[i] = s2[i - l1];
	join[i] = '\0';
	if (del == 1)
		free(s1);
	if (del == 2)
		free(s2);
	return (join);
}
