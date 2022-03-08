/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:23:54 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:24:01 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lg_nb(long n)
{
	int	i;

	i = 1;
	while ((n / 10) > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	fill_itoa(char	*itoa, long n, int ind)
{
	if ((n / 10) > 0)
	{
		fill_itoa(itoa, n / 10, ind - 1);
		fill_itoa(itoa, n % 10, ind);
	}
	if ((n / 10) == 0)
		itoa[ind] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*itoa;
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		itoa = malloc(sizeof(char) * lg_nb(nb) + 2);
		if (!itoa)
			return (0);
		itoa[0] = '-';
		fill_itoa(itoa, nb, lg_nb(nb));
		itoa[lg_nb(nb) + 1] = '\0';
		return (itoa);
	}
	itoa = malloc(sizeof(char) * lg_nb(nb) + 1);
	if (!itoa)
		return (0);
	fill_itoa(itoa, nb, lg_nb(nb) - 1);
	itoa[lg_nb(nb)] = '\0';
	return (itoa);
}
