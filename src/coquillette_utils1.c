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

void	feel_free(t_list *env)
{
	t_env	*var;
	
	while (env)
	{
		var = env->content;
		free(var->name);
		free(var->value);
		env = env->next;
	}
}

int	print_err(char *str, int err)
{
	ft_putendl_fd(str, 2);
	g_cmd_ret = err;
	return (1);
}

int	count_pipe(char *str)
{
	int	count;
	int	i;
	int	quote;
	int dquote;

	i = 0;
	count = 0;
	quote = 0;
	dquote = 0;
	while (str[i])
	{
		quote_switcher(&quote, &dquote, str[i]);
		if (str[i] == '|' && !quote && !dquote)
			count++;
		i++;
	}
	return (count);
}

void init_data(t_data *data, int i, char *str)
{
	if (i == 0)
	{
		if (i == 0)
		{
			data->nb_cmd = 1 + count_pipe(str);
			data->last_return = 0;
		}
		data->in = 0;
	}
	else
		data->in = -2;
	data->out = -2;
	data->argv = NULL;
	data->cmd_path = NULL;
}

t_env	*create_struct(char *env)
{
	t_env	*blop;

	blop = NULL;
	blop = malloc(sizeof(t_env));
	if (!blop)
		return (NULL);
	blop->name = ft_substr(env, 0, ft_strmchr(env, "=+") - env);
	if (ft_strrchr(env, '='))
		blop->eg = '=';
	else
		blop->eg = 'c';
	blop->value = ft_substr(ft_strchr(env, '='), 1, ft_strlen(env));
	blop->rank = 0;
	return (blop);
}

t_list	*init_envp(char **envp)
{
	t_list	*env;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	env = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(create_struct(envp[i]));
		if (!tmp)
			return (NULL); // free le reste de la liste chainee !!
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}

char	*rl_get(char *line_read)
{
/*	int	pid;

	pid = fork();
	if (pid == -1)*/
		
	if (line_read)
		free(line_read);
	line_read = readline("\e[34mcoquillette0.1>\e[0m");
	if (!line_read)
	{
		ft_putendl_fd("j'ai recu un \\0 donc je dois exit", 1);
		exit(EXIT_SUCCESS);
	}
	line_read = check_quote_end(line_read);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
