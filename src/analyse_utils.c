/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:40:11 by njaros            #+#    #+#             */
/*   Updated: 2022/03/31 16:18:30 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	quote_switcher(int *quote, int *dquote, char c)
{
	if (c == 34 && !*quote)
		*dquote = ft_switch(*dquote);
	if (c == 39 && !*dquote)
		*quote = ft_switch(*quote);
}

int	analyse_sep(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	analyse_error_message(char *str, int context)
{
	if (context == 1)
	{
		write(2, "coquillette: ", 14);
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 29);
	}
}

void	reorder_lst(t_list **lst, t_list *prev, int context)
{
	if (context == 1)
	{
		
	}
}