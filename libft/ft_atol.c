/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:21:15 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/26 13:29:46 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atol(const char *str, long long *nb)
{
	int			num;
	int			i;

	num = 1;
	i = 0;
	*nb = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			num = -num;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		*nb = *nb * 10 + (str[i] - '0') * num;
		if ((num == -1 && *nb > 0) || (num == 1 && *nb < 0))
			return (1);
		i++;
	}
	return (0);
}
