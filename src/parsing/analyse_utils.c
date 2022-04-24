/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:40:11 by njaros            #+#    #+#             */
/*   Updated: 2022/04/21 15:37:44 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	count_pipe(char *str)
{
	int	count;
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	count = 0;
	quote = 0;
	dquote = 0;
	while (str[i])
	{
		quote_switcher(&quote, &dquote, str[i]);
		if (str[i] == '|' && !quote && !dquote)
			count++;
		i++;
	}
	return (count);
}

void	init_data(t_data *data, int i, char *str)
{
	if (!i)
	{
		data->nb_cmd = 1 + count_pipe(str);
		data->in = 0;
	}
	if (i)
	{
		data->in = -2;
		ft_free(data->argv);
	}
	data->out = -2;
	data->argv = NULL;
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
