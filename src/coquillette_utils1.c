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
	char	*env;
	
	data->envp = envp;
	data->path = ft_split(env, ':');
	data->argv = NULL;
	return (0);
}
char	*rl_get(char *line_read)
{
	if (line_read)
		free(line_read);
	line_read = readline("coquillette0.1>");
	if (!line_read)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	line_read = check_quote_end(line_read);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

t_env	*create_struct(char *envp)
{
	t_env	*blop;

	blop = NULL;
	blop = malloc(sizeof(t_env));
	if (!blop)
		return (NULL);
	blop->name = ft_substr(envp, 0, ft_strchr(envp, '=') - envp);
	blop->value = ft_substr(ft_strchr(envp, '='), 1, ft_strlen(envp));
	return (blop);
}

t_list	*init_envp(char **envp)
{
	t_list	*env;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(create_struct(envp[i]));
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}
