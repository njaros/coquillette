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

void	print_error(char *cmd)
{
	ft_putstr_fd("coquillette: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
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
	static int	first_init = 1;

	if (first_init)
	{
		data->last_return = 0;
		first_init = 0;
	}
	if (!i)
	{
		data->nb_cmd = 1 + count_pipe(str);
		data->in = 0;
	}
	if (i)
	{
		data->in = -2;
		ft_free(data->argv);
	}
	data->out = -2;
	data->argv = NULL;
}

t_env	*create_struct(char *env)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_substr(env, 0, ft_strmchr(env, "=+") - env);
	if (ft_strrchr(env, '='))
		new->eg = '=';
	else
		new->eg = 'c';
	new->value = ft_substr(ft_strchr(env, '='), 1, ft_strlen(env));
	new->rank = 0;
	return (new);
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
		{
			ft_lstclear(&env, del); // a vérifier !!
			return (NULL);
		}
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}

char	*rl_get(char *line_read, t_data *data)
{
	char	*prompt;

	prompt = prompt_builder(data);
	if (line_read)
		free(line_read);
	line_read = readline(prompt);
	free(prompt);
	if (!line_read)
	{
		terminal_handler(1);
		ft_putendl_fd("\nexit", 1);
		exit(WEXITSTATUS(data->last_return));
	}
	line_read = check_quote_end(line_read);
	if (line_read && *line_read)
		add_history(line_read);
	line_read = heredoc_handler(line_read);
	return (line_read);
}
