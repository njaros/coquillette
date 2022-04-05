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

char	*ft_strmchr(char *s, char *charset)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
		{
			if (s[i] == charset[j])
				return (&s[i]);
			j++;
		}
		i++;
	}
	if (s[i] == charset[j])
		return (&s[i]);
	return (0);
}

t_env	*find_env_var(t_list *env, char *to_search)
{
	t_env	*var;
	
	var = NULL;
	while (env)
	{
		var = env->content;
		if (!ft_strcmp(var->name, to_search))
			break ;
		env = env->next;
	}
	return (var);
}

void init_data(t_data *data, int i)
{
	data->last_return = 0;
	if (i == 0)
		data->in = 0;
	else
		data->in = -2;
	data->out = -2;
	data->argv = NULL;
	data->cmd_path = NULL;
}

char	*rl_get(char *line_read)
{
	if (line_read)
		free(line_read);
	line_read = readline("\e[34mcoquillette0.1>\e[0m");
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
			return (NULL);
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}