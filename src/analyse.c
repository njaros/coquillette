/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:00:42 by njaros            #+#    #+#             */
/*   Updated: 2022/03/28 16:36:30 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	quote_detector(char c, int *in_quote)
{
	static int	quote = 0;
	static int	dquote = 0;

	if (!quote && c == 34)
	{
		dquote = ft_switch(dquote);
		if (dquote == 1)
			*in_quote = 1;
		else
			*in_quote = 0;
		return (1);
	}
	if (!dquote && c == 39)
	{
		quote = ft_switch(quote);
		if (dquote == 1)
			*in_quote = 1;
		else
			*in_quote = 0;
		return (1);
	}
	return (0);
}

char	*analyse(char *str, int *i, int lg)
{
	char	*content;
	int		j;

	content = malloc(lg + 1);
	if (!content)
		return (NULL);
	ft_bzero(content, lg + 1);
	j = -1;
	while (str[*i] && !(str[*i] == ' ' && )
}

t_list	*mise_en_liste(char *str)
{
	int		i;
	t_list	*lst;
	t_list	*secure;
	char	*content;
	
	i = -1;
	while (str[++i] == ' ')
		;
	while (str[i] && str[i] != '|')
	{
		content = analyse(&str[i], &i, ft_strlen(&str[i]));
		secure = ft_lstnew(content);
		if (!secure || !content)
		{
			ft_lstclear(&lst, free);
			ft_lstdelone(secure, free);
			free(content);
			return(NULL);
		}
		ft_lstadd_back(&lst, secure);
		while (str[i] == ' ')
			i++;
	}
	return (lst);
}