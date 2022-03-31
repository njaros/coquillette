/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:00:42 by njaros            #+#    #+#             */
/*   Updated: 2022/03/30 12:02:10 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

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

void	quote_switcher(int *quote, int *dquote, char c)
{
	if (c == 34 && !*quote)
		*dquote = ft_switch(*dquote);
	if (c == 39 && !*dquote)
		*quote = ft_switch(*quote);
}

int	ajout_block(t_data *pouet, int i, int *ptr, char *str)
{
	char	*sub;

	sub = ft_substr(str, *ptr, i - *ptr);
	if (!sub)
		return (0);
	*ptr = i + 1;
}

char	*analyse(char *str, int *i, t_data *data)
{
	t_list	*pouet;
	int		ptr;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	ptr = *i;
	pouet = NULL;
	while (str[*i] && str[*i] != '|')
	{
		quote_switcher(&quote, &dquote, str[*i]);
		if (str[*i] == ' ' && !quote && !dquote)
			if (!ajout_block(&pouet, *i, &ptr, str))
				return (free_lst_analyse(&pouet));
		*i += 1;
	}
	return (organiser(&pouet, *i, data));
}
