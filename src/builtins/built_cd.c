/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:15:00 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/26 11:40:42 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	change_pwd_oldpwd(char *oldpwd, t_list *env)
{
	t_env	*tmp;
	char	pwd[MAXPATHLEN];
	char	*var_name;

	getcwd(pwd, MAXPATHLEN);
	tmp = find_env_var(env, "PWD");
	var_name = ft_strjoin("PWD=", pwd);
	if (!var_name)
		error("built_cd: change_pwd_oldpwd: var_name");
	replace_or_create(env, tmp, var_name, pwd);
	free(var_name);
	tmp = find_env_var(env, "OLDPWD");
	var_name = ft_strjoin("OLDPWD=", oldpwd);
	if (!var_name)
		error("built_cd: change_pwd_oldpwd: var_name");
	replace_or_create(env, tmp, var_name, oldpwd);
	free(var_name);
}

int	move_to(t_data *data)
{
	int		i;

	i = 0;
	if (data->argv[1][i] == '~')
	{
		if (to_home(data, data->argv[1][i]))
			return (1);
		i = 2;
	}
	if (!opendir(&data->argv[1][i]))
	{
		print_error(data, data->argv[1], NULL, 1);
		return (1);
	}
	data->last_return = chdir(&data->argv[1][i]);
	if (data->last_return == -1)
	{
		print_error(data, data->argv[1], NULL, -1);
		return (1);
	}
	return (0);
}

int	dash(t_data *data)
{
	t_env	*tmp;

	if (data->out == -1)
	{
		data->last_return = 1;
		return (1);
	}
	tmp = find_env_var(data->env, "OLDPWD");
	if (!tmp)
	{
		print_error(data, NULL, "OLDPWD not set", 1);
		return (1);
	}
	ft_putendl_fd(tmp->value, data->out);
	data->last_return = chdir(tmp->value);
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
		print_error(data, NULL, "HOME not set", 1);
		return (1);
	}
	data->last_return = chdir(home);
	return (0);
}

int	built_cd(t_data *data)
{
	char	oldpwd[MAXPATHLEN];

	data->last_return = 0;
	getcwd(oldpwd, MAXPATHLEN);
	if (!data->argv[1])
	{
		if (to_home(data, 0))
			return (1);
	}
	else if (data->argv[1][0] == '-')
	{
		if (dash(data))
			return (1);
	}
	else if (move_to(data))
		return (1);
	change_pwd_oldpwd(oldpwd, data->env);
	return (0);
}
