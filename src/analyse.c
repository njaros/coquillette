/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:00:42 by njaros            #+#    #+#             */
/*   Updated: 2022/03/30 11:12:17 by njaros           ###   ########lyon.fr   */
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

char	*analyse(char *str, int *i, t_data *data)
{
	char	*content;
	int		j;
	int		quote;

	quote = 0;
	content = malloc(lg + 2); // +2 car il est possible qu'un $? devienne 127 (ou autre)
	if (!content)
		return (NULL);
	ft_bzero(content, lg + 2); // Valgrind va râler...
	j = -1;
	while (str[*i] && !(ft_tokenchar(str[*i]) && quote))
	{}
}

/*t_list	*mise_en_liste(char *str)
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
*/