/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd_rdonly.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:16:31 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/07 10:19:12 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_fd_rdonly(char *entry)
{
	int	i;
	int	fd;

	i = -1;
	while (entry[++i])
	{
		if (entry[i] < '0' && entry[i] > '9')
			return (open(entry, O_RDONLY));
	}
	fd = open(entry, O_RDONLY);
	if (fd < 0)
		return (ft_atoi(entry));
	else
		return (fd);
}
