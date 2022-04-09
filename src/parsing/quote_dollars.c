/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:26:54 by njaros            #+#    #+#             */
/*   Updated: 2022/04/08 16:00:58 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*quotage(char *str, int *dquote, int *quote)
{
	char	*add;
	char	*join;
	int		i;

	i = -1;
	add = readline("> ");
	if (!add)
	{
		if (*dquote)
			return (eof_detector(str, 1));
		return (eof_detector(str, 2));
	}	
	while (add[++i])
		quote_switcher(quote, dquote, add[i]);
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

char	*eof_detector(char *to_free, int context)
{
	char	del;

	del = 127;
	if (context)
	{
		write(2, &del, 1);
		ft_putstr_fd("coquillette: unexpected EOF while looking for matching `", 2);
	}
	if (context == 1)
		ft_putendl_fd("\"'", 2);
	if (context == 2)
		ft_putendl_fd("''", 2);
	ft_putendl_fd("coquillette: syntax error: unexpected end of file", 2);
	return (NULL);
}