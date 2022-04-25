/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_doll_handler2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:17:55 by njaros            #+#    #+#             */
/*   Updated: 2022/04/25 13:29:31 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	trap_dollz(char b)
{
	if (b == ' ' || b == 39 || b == 34
		|| b == '<' || b == '>' || b == '|'
		|| b == '%' || b == '^' || b == '='
		|| b == '+' || b == '\0' || b == '/'
		|| b == ',' || b == ':' || b == '$'
		|| b == '#')
		return (1);
	return (0);
}

int	law_to_print(char a, char q, char b)
{
	if (!q && (a == 34 || a == 39))
		return (0);
	if (a == q)
		return (0);
	if (a == '$' && q != 39 && !trap_dollz(b))
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
		error("coquillette: analyse: only_quote_handler");
	while (str[++i])
	{
		q_val = handler_switcher(str[i], q_val);
		if (law_to_print(str[i], q_val, 0))
			ret[++j] = str[i];
	}
	return (ret);
}
