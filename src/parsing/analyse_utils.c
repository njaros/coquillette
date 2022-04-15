/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:40:11 by njaros            #+#    #+#             */
/*   Updated: 2022/04/07 14:59:20 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	ft_switch(int n)
{
	if (n)
		return (0);
	return (1);
}

void	quote_switcher(int *quote, int *dquote, char c)
{
	if (c == 34 && !*quote)
		*dquote = ft_switch(*dquote);
	if (c == 39 && !*dquote)
		*quote = ft_switch(*quote);
}

int	analyse_sep(char *str, int *i, int context)
{
	if (str[*i] == ' ' || str[*i] == '<' || str[*i] == '>')
		return (1);
	if (str[*i + 1] == '|' && context)
	{
		*i += 1;
		return (1);
	}
	if (!str[*i + 1] && context)
	{
		*i += 1;
		return (1);
	}
	return (0);
}

void	init_analyse(char *str, int *i, int *ptr)
{
	while (str[*i] == ' ')
		*i += 1;
	*ptr = *i;
	while (str[*i] && analyse_sep(str, i, 0))
		*i += 1;
}
