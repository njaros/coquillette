/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:10:44 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/19 11:38:13 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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
		if (!first)
			error("malloc");
		envp[i] = ft_strjoin(first, tmp->value);
		if (!envp[i])
			error("malloc");
		free(first);
		i++;
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
}

char	*get_path(char *cmd, char **path)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	cmd_path = NULL;
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			error("malloc");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			error("malloc");
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (cmd_path);
}

int	check_path(char *entry)
{
	int	i;

	i = -1;
	// gérer Is a directory ?!
	while (entry[++i])
	{
		if (entry[i] == '/')
		{
			if (!opendir(entry) && errno == ENOENT)
			{
				print_error(entry);
				return (-1);
			}
			else
			{
				if (access(entry, X_OK) == 0)
					return (1);
				else
				{
					print_error(entry);
					return (-1);
				}
			}
		}
	}
	return (0);
}

char	*found_cmd(char *entry, t_list *env)
{
	char	*cmd;
	char	**path_tab;
	int		ck;
	t_env	*tmp;

	ck = check_path(entry);
	if (ck == 1)
		return (entry);
	if (ck == -1)
		return (NULL);
	tmp = find_env_var(env, "PATH");
	if (!tmp)
	{
		print_error(entry); // vérifier message si path unset
		return (NULL);
	}
	path_tab = ft_split(tmp->value, ':');
	if (!path_tab)
		error("malloc");
	cmd = get_path(entry, path_tab);
	if (!cmd)
		print_error(entry);
	ft_free(path_tab);
	dprintf(2, "%s\n", cmd);
	return (cmd);
}
