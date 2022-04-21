/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:15:00 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/21 16:37:40 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	change_pwd_oldpwd(char *oldpwd, t_list *env)
{
	t_env	*tmp;
	t_list	*new;
	char	pwd[MAXPATHLEN];
	char	*var_name;

	if (!getcwd(pwd, MAXPATHLEN))
		return (print_err("getcwd() error", errno));
	tmp = find_env_var(env, "PWD");
	var_name = ft_strjoin("PWD=", pwd);
	replace_or_create(env, tmp, var_name, pwd);
	free(var_name);
	tmp = find_env_var(env, "OLDPWD");
	var_name = ft_strjoin("OLDPWD=", oldpwd);
	replace_or_create(env, tmp, var_name, oldpwd);
	free(var_name);
	return (0);
}

int	to_home(t_data *data, char c)
{
	char	*home;
	t_env	*tmp;

	home = NULL;
	if (c == '~')
		home = getenv("HOME");
	else
	{
		tmp = find_env_var(data->env, "HOME");
		if (tmp)
			home = ft_strdup(tmp->value);	
	}
	if (!home)
	{
		print_error("cd", "HOME not set");
		data->last_return = 1;
		return (1);
	}
	data->last_return = chdir(home);
	return (0);
}

void	built_cd(t_data *data)
{
	char	oldpwd[MAXPATHLEN];
	t_env	*tmp;
	int		i;

	i = 0;
	data->last_return = 0;
	tmp = NULL;
	kill(0, SIGUSR1);
	getcwd(oldpwd, MAXPATHLEN);
	if (!data->argv[1])
	{
		to_home(data, 0);
		exit(data->last_return);
	}
	if (data->argv[1][i] == '-')
	{
		tmp = find_env_var(env, "OLDPWD");
		if (!tmp)
		{
			print_error(data->argv[0], "OLDPWD not set");
			data->last_return = 1;
			exit(data->last_return);
		}
		ft_putendl_fd(tmp->value, fd);
		data->last_return = chdir(tmp->value);
	}
	else
	{
		if (data->argv[1][i] == '~')
		{
			if (to_home(data, data->argv[1][i]) != 0)
				exit(data->last_return);
			i = 2;
		}
		if (data->argv[1][i])
		{
			if (!opendir(&data->argv[1][i]))
				return (print_err("cd: Permission denied", 1));
			data->last_return = chdir(&data->argv[1][i]);
			if (data->last_return == -1)
				return (print_err("No such file or directory", 1));
		}
	}
	if (change_pwd_oldpwd(oldpwd, env) != 0)
		return (1);
	exit(data->last_return);
}
// too many arguments ?!