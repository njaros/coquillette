/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:58:06 by njaros            #+#    #+#             */
/*   Updated: 2022/03/31 17:23:26 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	organiser(t_list **pouet, int *i, char *str, t_data *data)
{
	t_list	*first;
	int		lg;
	int		i;

	i = -1;
	lg = chevronnage(pouet, data);
	first = *pouet;
	data->argv = malloc(sizeof(char *) * lg + 1);
	if (!data->argv)
		return (free_lst_analyse(pouet));
	data->argv[lg] = NULL;
	while (*pouet)
	{
		data->argv[++i] = (*pouet)->content;
		*pouet = (*pouet)->next;
	}
	if (str[*i] == '|')
	{
		*i += 1;
		return (1);
	}
	return (0);
}