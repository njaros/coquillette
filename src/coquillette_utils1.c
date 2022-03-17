/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coquillette_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:20:42 by njaros            #+#    #+#             */
/*   Updated: 2022/03/08 16:46:37 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int init_pipex_data(pipex_data *data, char **envp)
{
	data->envp = envp;
	data->path = NULL;
	data->argv = NULL;
	return (0);
}

char	*check_quote_end(char *str)
{
	int	i;
	int	quote;
	int	dquote;

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
	if (!dquote && !quote)
		return (str);
	if (dquote)
		
}

char	*dollar_searcher(char *str)
{
	int		i;
	int		quote;
	t_list	*dollar;

	dollar = NULL;
	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str == 39)
			quote = ft_switch(quote);
		if (str == '$' && !quote)
			ft_lstadd_back()
	}
}

char	*rl_get(char *line_read)
{
	if (line_read)
		free(line_read);
	line_read = readline("coquillette0.1>");
	if (!line_read)
	{
		ft_putendl_fd("\nexit", 1);
		exit(EXIT_SUCCESS);
	}
	line_read = check_quote_end(line_read);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
