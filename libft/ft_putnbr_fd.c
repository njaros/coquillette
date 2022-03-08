/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:28:51 by njaros            #+#    #+#             */
/*   Updated: 2021/11/02 15:28:54 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_recuputnbr_fd(long n, int fd)
{
	if (n / 10 > 0)
	{
		ft_recuputnbr_fd((n / 10), fd);
		ft_recuputnbr_fd((n % 10), fd);
	}
	if (n / 10 == 0)
		ft_putchar_fd(n + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	k;

	k = (long) n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		k = -k;
	}
	ft_recuputnbr_fd(k, fd);
}
