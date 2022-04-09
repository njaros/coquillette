/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:52:47 by njaros            #+#    #+#             */
/*   Updated: 2022/03/29 15:52:47 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	is_only_blank(char *add)
{
	int	i;

	if (!add)
		return (1);
	i = -1;
	while (add[++i])
		if (add[i] != ' ')
		{
			free(add);
			return (0);
		}
	free(add);
	add = NULL;
	return (1);
}

char	*pipage(char *str)
{
	char	*piped;
	char	*add;
	int		i;

	add = NULL;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ' && i >= 0)
		i--;
	if (i < 0 || str[i] != '|')
		return (str);
	while (is_only_blank(add))
	{
		add = readline("> ");
		piped = ft_strjoin(str, add);
		free(str);
		if (!add)
			return (eof_detector(piped, 0));
		str = piped;
	}
	return (piped);
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
			if (ft_tokenchar(str[*i]) &&
					!(pipe && (!str[*i] || str[*i] == '<' || str[*i] == '>')))
				return (1);
			*i -= 1;
		}
	}
	return (0);
}

char	*cherche_merde(char *str, int *quote, int *dquote)
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
