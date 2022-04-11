/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:10:44 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/11 13:57:20 by ccartet          ###   ########.fr       */
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
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = env->content;
		first = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(first, tmp->value);
		free(first);
		i++;
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
}

char    *get_path(char *cmd, char **path)
{
    char    *cmd_path;
    char    *tmp;
    int     i;

    cmd_path = NULL;
    i = 0;
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(cmd_path, X_OK) == 0)
            break ;
        free(cmd_path);
        cmd_path = NULL;
        i++;
    }
    return (cmd_path);
}

char	*found_cmd(char *entry, t_list *env)
{
	char	*cmd;
	char	**path_tab;
	int		i;
	t_env	*tmp;
	
	i = -1;
	while (entry[++i])
	{
		if (entry[i] == '/')
		{
			if (access(entry, X_OK) == 0)
				return (entry);
			else
				return (NULL);
		}
	}
	tmp = find_env_var(env, "PATH");
	if (!tmp)
		return (NULL);
	path_tab = ft_split(tmp->value, ':');
	cmd = get_path(entry, path_tab);
	ft_free(path_tab);
	return (cmd);
}