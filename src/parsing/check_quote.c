/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:26:54 by njaros            #+#    #+#             */
/*   Updated: 2022/04/21 14:56:47 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*check_quote_end(char *str)
{
	int		quote;
	int		dquote;

	str = guilty_searcher(str, &quote, &dquote);
	if (str)
	{
		if (dquote)
			ft_putendl_fd("coquillette: double quote not closed", 2);
		if (quote)
			ft_putendl_fd("coquillette: quote not closed", 2);
		if (last_char_is_pipe(str) && !quote && !dquote)
			ft_putendl_fd("coquillette: pipe at end of line", 2);
		if (dquote || quote || last_char_is_pipe(str))
		{
			add_history(str);
			free(str);
			str = NULL;
		}
	}
	return (str);
}

int	double_token_char(char *str, int *quote, int *dquote, int *i)
{
	int	pipe;

	while (str[++(*i)])
	{
		pipe = 0;
		quote_switcher(quote, dquote, str[*i]);
		if (ft_tokenchar(str[*i]) && !*quote && !*dquote)
		{
			if (str[(*i)] == '|')
				pipe = 1;
			if ((str[*i] == '>' && str[*i + 1] == '>')
				|| (str[*i] == '<' && str[*i + 1] == '<'))
				*i += 1;
			while (str[++(*i)] == ' ')
				;
			if (ft_tokenchar(str[*i]) && !(pipe && (!str[*i]
						|| str[*i] == '<' || str[*i] == '>')))
				return (1);
			*i -= 1;
		}
	}
	return (0);
}

char	*guilty_searcher(char *str, int *quote, int *dquote)
{
	int	i;

	*quote = 0;
	*dquote = 0;
	if (!str)
		return (NULL);
	i = -1;
	if (double_token_char(str, quote, dquote, &i)
		|| first_char_is_pipe(str, &i))
	{
		add_history(str);
		le_coupable_est(&str[i]);
		free(str);
		return (NULL);
	}
	return (str);
}
