/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:26:54 by njaros            #+#    #+#             */
/*   Updated: 2022/04/08 13:16:58 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*quotage(char *str, int *dquote, int *quote)
{
	char	*add;
	char	*join;
	int		i;

	i = -1;
	add = readline(">");
	while (add[++i])
	{
		if (add[i] == 34 && !*quote)
			*dquote = ft_switch(*dquote);
		if (add[i] == 39 && !*dquote)
			*quote = ft_switch(*quote);
	}
	join = ft_strjoin("\n", add);
	free(add);
	add = ft_strjoin(str, join);
	free(str);
	free(join);
	return (add);
}

char	*check_quote_end(char *str)
{
	int		quote;
	int		dquote;
	char	*next;

	quote = 0;
	dquote = 0;
	str = cherche_merde(str, &quote, &dquote);
	while (str && ((dquote || quote) || last_char_is_pipe(str)))
	{
		if (dquote || quote)
			str = quotage(str, &dquote, &quote);
		else if (last_char_is_pipe(str))
			str = pipage(str);
		str = cherche_merde(str, &quote, &dquote);
	}
	return (str);
}
