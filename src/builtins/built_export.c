/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:17:08 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/30 13:53:44 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	init_rank(t_list *env, int *size)
{
	t_env	*tmp;
	t_env	*actuel;
	t_list	*next;
	t_list	*env_bis;
	int		index;

	env_bis = env;
	while (env)
	{
		index = 1;
		actuel = env->content;
		next = env_bis;
		while (next)
		{
			tmp = next->content;
			if (ft_strcmp(actuel->name, tmp->name) > 0)
				index++;
			next = next->next;
		}
		actuel->rank = index;
		env = env->next;
		*size += 1;
	}
}

void	print_export(t_list *env, int size, int fd)
{
	t_env	*tmp;
	t_list	*env_tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (i <= size)
	{
		env_tmp = env;
		while (env_tmp)
		{
			tmp = env_tmp->content;
			if (tmp->rank == i)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(tmp->name, fd);
				if (tmp->value)
				{
					ft_putstr_fd("=\"", fd);
					ft_putstr_fd(tmp->value, fd);
					ft_putchar_fd('\"', fd);
				}
				ft_putchar_fd('\n', fd);
				break ;
			}
			env_tmp = env_tmp->next;
		}
		i++;
	}
}

int	built_export(char **cmd_arg, t_list *env, int fd)
{
	int		i;
	t_env	*tmp;
	char	*to_search;
	char	*value;
	int		size;
	int		a;

	i = 1;
	size = 0;
	g_cmd_ret = 0;
	if (!cmd_arg[1])
	{
		init_rank(env, &size);
		print_export(env, size, fd);
	}
	while (cmd_arg[i])
	{
		to_search = ft_substr(cmd_arg[i], 0, ft_strmchr(cmd_arg[i], "=+") - cmd_arg[i]);
		a = -1;
		while (to_search[a++])
		{
			if (!ft_isdigit(to_search[a]))
				return (print_err("not a valid identifier", 1));
		}
		tmp = find_env_var(env, to_search);
		free(to_search);
		value = ft_substr(ft_strchr(cmd_arg[i], '='), 1, ft_strlen(cmd_arg[i])); // vérifier comportement si rien après le =, \0 ??
		replace_or_create(env, tmp, cmd_arg[i], value);
		i++;
	}
	return (0);
}
// attention ! tester export NAME=, et ensuite env, je dois voir cette nouvelle variable apparaitre