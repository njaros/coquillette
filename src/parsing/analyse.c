/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:00:42 by njaros            #+#    #+#             */
/*   Updated: 2022/04/19 11:47:27 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

// La fonction ci-dessous est beaucoup plus utile que vous ne le pensez
void	do_nothing(void *let_him_alive)
{
	(void)let_him_alive;
}

int	ajout_block(t_list **pouet, int *i, int *ptr, char *str)
{
	char	*sub;
	t_list	*new;

	sub = ft_substr(str, *ptr, *i - *ptr);
	if (!sub)
		return (0);
	while (str[*i] == ' ')
		*i += 1;
	*ptr = *i;
	new = ft_lstnew(sub);
	if (!new)
	{
		free(sub);
		return (0);
	}
	ft_lstadd_back(pouet, new);
	while (analyse_sep(str, i, 0))
		*i += 1;
	return (1);
}

int	analyse(char *str, int *i, t_data *data)
{
	t_list	*pouet;
	int		ptr;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	pouet = NULL;
	init_data(data, *i, str);
	if (!str)
		return (0);
	init_analyse(str, i, &ptr);
	while (str[*i] && !(str[*i] == '|' && !quote && !dquote))
	{
		quote_switcher(&quote, &dquote, str[*i]);
		if ((analyse_sep(str, i, 1) && !quote && !dquote))
		{
			if (!ajout_block(&pouet, i, &ptr, str))
				error("analyse: ajout_block");
		}
		else
			*i += 1;
	}
	return (organiser(&pouet, i, str, data));
}
