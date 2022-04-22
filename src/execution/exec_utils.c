/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:10:44 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/22 15:56:48 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	error(char *msg)
{
	perror(msg);
	// exit(EXIT_FAILURE);
}

char	**list_to_tab(t_list *env)
{
	char	**envp;
	int		size;
	int		i;
	t_env	*tmp;
	char	*first;

	size = ft_lstsize(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		error("malloc");
	i = 0;
	while (env)
	{
		tmp = env->content;
		first = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(first, tmp->value);
		if (!first || !envp[i])
			error("malloc");
		free(first);
		i++;
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
}

void	transform_fds(t_data *data, int fd_in, int fd_out)
{
	if (data->in == -2)
		data->in = fd_in;
	if (data->out == -2)
		data->out = fd_out;
}

int	check_is_builtin(t_data *data)
{
	if (!ft_strcmp(data->argv[0], "echo"))
		return (0);
	else if (!ft_strcmp(data->argv[0], "cd"))
		return (0);
	else if (!ft_strcmp(data->argv[0], "pwd"))
		return (0);
	else if (!ft_strcmp(data->argv[0], "export"))
		return (0);
	else if (!ft_strcmp(data->argv[0], "unset"))
		return (0);
	else if (!ft_strcmp(data->argv[0], "env"))
		return (0);
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd == 1)
		return (0);
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd != 1)
		return (0);
	return (-1);
}

int	do_builtins(t_data *data)
{
	if (!ft_strcmp(data->argv[0], "echo"))
		return (built_echo(data));
	else if (!ft_strcmp(data->argv[0], "cd"))
		return (built_cd(data));
	else if (!ft_strcmp(data->argv[0], "pwd"))
		return (built_pwd(data));
	else if (!ft_strcmp(data->argv[0], "export"))
		return (built_export(data));
	else if (!ft_strcmp(data->argv[0], "unset"))
		return (built_unset(data));
	else if (!ft_strcmp(data->argv[0], "env"))
		return (built_env(data));
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd == 1)
		return (built_exit(data));
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd != 1)
		return (0);
	return (-1);
}
