/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:10:44 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/21 14:03:25 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	error(char *msg)
{
	perror(msg);
	// exit(EXIT_FAILURE);
}

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
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
