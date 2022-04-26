/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:42:40 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/26 11:50:04 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

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
			error("found_cmd: get_path: tmp");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			error("found_cmd: get_path: cmd_path");
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (cmd_path);
}

int	is_a_directory(t_data *data, char *entry)
{
	char	**path_tab;
	int		j;
	char	*blop;

	path_tab = ft_split(getenv("PATH"), ':');
	if (!path_tab)
		error("found_cmd: is_a_directory: path_tab");
	j = 0;
	while (path_tab[j])
	{
		blop = ft_strjoin(path_tab[j], "/");
		if (!blop)
			error("found_cmd: is_a_directory: blop");
		if (!ft_strcmp(blop, entry))
		{
			print_error(data, NULL, "is a directory", 126);
			free(path_tab);
			free(blop);
			return (-1);
		}
		free(blop);
		j++;
	}
	free(path_tab);
	return (0);
}

int	check_absolute_path(t_data *data, char *entry)
{
	int	i;

	i = -1;
	while (entry[++i])
	{
		if (entry[i] == '/')
		{
			if (!opendir(entry) && errno == ENOENT)
			{
				print_error(data, NULL, NULL, 127);
				return (-1);
			}
			if (is_a_directory(data, entry) == -1)
				return (-1);
			if (access(entry, X_OK) == 0)
				return (1);
			print_error(data, NULL, NULL, 126);
			return (-1);
		}
	}
	return (0);
}

char	*found_cmd(t_data *data, char *entry, t_list *env)
{
	char	*cmd;
	char	**path_tab;
	int		ck;
	t_env	*tmp;

	ck = check_absolute_path(data, entry);
	if (ck == 1)
		return (entry);
	if (ck == -1)
		return (NULL);
	tmp = find_env_var(env, "PATH");
	if (!tmp)
	{
		print_error(data, NULL, "command not found", 127);
		return (NULL);
	}
	path_tab = ft_split(tmp->value, ':');
	if (!path_tab)
		error("found_cmd: path_tab");
	cmd = get_path(entry, path_tab);
	if (!cmd)
		print_error(data, NULL, "command not found", 127);
	ft_free(path_tab);
	return (cmd);
}
