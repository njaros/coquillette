/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:33:05 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:33:07 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*trim;

	if ((s1 == NULL) || (set == NULL))
		return (NULL);
	k = 0;
	i = 0;
	j = 0;
	while ((is_charset(s1[i], set)) && (s1[i]))
		i++;
	while (s1[j])
		j++;
	while ((is_charset(s1[j], set) && (i < j)) || (s1[j] == '\0' && (i < j)))
		j--;
	trim = malloc(sizeof(char) * (j - i) + 2);
	if (!trim)
		return (NULL);
	while (i <= j)
		trim[k++] = s1[i++];
	trim[k] = '\0';
	return (trim);
}
