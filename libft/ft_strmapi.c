/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:31:59 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:32:01 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*happy;
	size_t	i;

	if ((s == NULL) || ((*f) == NULL))
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	happy = malloc (sizeof(char) * i + 1);
	if (!happy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		happy[i] = (*f)(i, s[i]);
		i++;
	}
	happy[i] = '\0';
	return (happy);
}
