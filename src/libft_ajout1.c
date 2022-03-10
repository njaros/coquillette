/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ajout1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:55:34 by njaros            #+#    #+#             */
/*   Updated: 2022/03/10 13:42:41 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

//get_fd retourne atoi(entry) si entry est seulement composé de chiffres,
//sinon il retourne en read_only le fd du fichier du même nom s'il existe.

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
