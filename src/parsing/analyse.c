/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:00:42 by njaros            #+#    #+#             */
/*   Updated: 2022/04/05 10:30:17 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

// La fonction ci-dessous est beaucoup plus utile que vous ne le pensez
void	do_nothing(void *let_him_alive)
{
	(void)let_him_alive;
}

char	*last_return(char *str, int *i, int ret)
{
	char	*number;
	char	*sub;
	char	*tmp;

	number = ft_itoa(ret);
	sub = ft_substr(str, 0, *i);
	tmp = ft_strjoin(sub, number);
	free(sub);
	sub = ft_substr(str, *i + 2, ft_strlen(str));
	*i += ft_strlen(number) - 1;
	free(number);
	number = ft_strjoin(tmp, sub);
	free(str);
	free(tmp);
	free(sub);
	return (number);
}

char	*dollz_what(char *str, t_data *data)
{
	int	quote;
	int	dquote;
	int	i;

	quote = 0;
	dquote = 0;
	i = -1;
	while (str[++i] && str[i] != '|')
	{
		quote_switcher(&quote, &dquote, str[i]);
		if (str[i] == '$' && !quote && !dquote)
		{
			str = last_return(str, &i, data->last_return);
			if (!str)
				return (NULL);
		}
	}
	return (str);
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
	init_data(data, *i);
	str = dollz_what(str, data);
	if (!str)
		return (0);
	init_analyse(str, i, &ptr);
	while (str[*i] && !(str[*i] == '|' && !quote && !dquote))
	{
		quote_switcher(&quote, &dquote, str[*i]);
		if ((analyse_sep(str, i, 1) && !quote && !dquote))
		{
			if (!ajout_block(&pouet, i, &ptr, str))
				return (free_lst_analyse(&pouet));
		}
		else
			*i += 1;
	}
	return (organiser(&pouet, i, str, data));
}
