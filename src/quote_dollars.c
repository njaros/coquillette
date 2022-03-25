/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:26:54 by njaros            #+#    #+#             */
/*   Updated: 2022/03/24 17:11:11 by njaros           ###   ########lyon.fr   */
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
	int		i;
	int		quote;
	int		dquote;
	char	*next;

	quote = 0;
	dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && !quote)
			dquote = ft_switch(dquote);
		if (str[i] == 39 && !dquote)
			quote = ft_switch(quote);
	}
	while (dquote || quote)
		str = quotage(str, &dquote, &quote);
	return (str);
}

char	*replace_dollz(char *str, int *i, int end)
{
	char	*replaced;
	char	*sub1;
	char	*sub2;
	char	*no_dollz;

	if (*i == 0)
		sub1 = ft_strdup("");
	else
		sub1 = ft_substr(str, 0, *i);
	sub2 = ft_substr(str, *i + 1, end - (*i + 1));
	no_dollz = ft_strjoin(sub1, getenv(sub2));
	free(sub1);
	sub1 = ft_substr(str, end, ft_strlen(str));
	i += ft_strlen(getenv(sub2));
	free(sub2);
	replaced = ft_strjoin(no_dollz, sub1);
	free(no_dollz);
	free(sub1);
	free(str);
	return (replaced);
}

char	*dollar_searcher(char *str)
{
	int		i;
	int		end;
	int		quote;
	char	*dollar;

	quote = 0;
	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == 39)
			quote = ft_switch(quote);
		if (str[i] == '$' && !quote)
		{
			end = i + 1;
			while (str[end] && !ft_metachar(str[end]))
				end++;
			str = replace_dollz(str, &i, end);
		}
	}
	return (str);
}
