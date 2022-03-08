/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:29:31 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:29:34 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	nb_str(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] && (s[i] != c))
			i++;
		while (s[i] && (s[i] == c))
			i++;
	}
	return (count);
}

char	*fill_adr(const char *str, char c)
{
	char	*filled;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while ((str[i] != c) && str[i])
		i++;
	filled = malloc(sizeof(char) * i + 1);
	if (!filled)
		return (NULL);
	while (j < i)
	{
		filled[j] = str[j];
		j++;
	}
	filled[j] = '\0';
	return (filled);
}

char	**free_split(char **split, size_t j)
{
	while (j != 0)
	{
		if (split[j] != NULL)
			free (split[j]);
		j--;
	}
	free (split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**adr;
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	j = 0;
	i = nb_str(s, c);
	adr = malloc(sizeof(char *) * (i + 1));
	if (!adr)
		return (NULL);
	while (j < i)
	{
		while (s[k] == c)
			k++;
		adr[j] = fill_adr(&s[k], c);
		if (!adr[j])
			return (free_split(adr, j));
		while ((s[k] != c) && s[k])
			k++;
		j++;
	}
	adr[j] = NULL;
	return (adr);
}
