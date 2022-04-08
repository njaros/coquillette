/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_doll_handler2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:17:55 by njaros            #+#    #+#             */
/*   Updated: 2022/04/08 11:17:18 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	law_to_print(char a, char q, int context)
{
	if (!q && (a == 34 || a == 39))
		return (0);
	if (a == q)
		return (0);
	if (a == '$' && q != 39 && context)
		return (0);
	return (1);
}

char	*only_quote_handler(char *str)
{
	char	*ret;
	char	q_val;
	int		i;
	int		j;

	i = -1;
	j = -1;
	q_val = 0;
	ret = calloc(1, ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		q_val = handler_switcher(str[i], q_val);
		if (law_to_print(str[i], q_val, 0))
			ret[++j] = str[i];
	}
	return (ret);
}