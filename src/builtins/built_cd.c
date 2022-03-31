/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:15:00 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/31 14:42:44 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	replace_or_create(t_list *env, t_env *var, char *var_name, char *path)
{
	t_list	*new;
	char	*tmp;

	new = NULL;
	if (!var)
	{
		new = ft_lstnew(create_struct(var_name));
		if (!new)
			return (print_err("lst problem", 1));
		ft_lstadd_back(&env, new);
	}
	else
	{
		if (ft_strrchr(var_name, '+'))
		{
			tmp = ft_strjoin(var->value, path);
			free(var->value);
			var->value = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			free(var->value);
			var->value = ft_strdup(path);
		}
	}
	return (0);
}

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

int	to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (print_err("cd : HOME not set", errno));
	g_cmd_ret = chdir(home);
	return (0);
}

int	built_cd(char **cmd_arg, t_list *env, int fd)
{
	char	oldpwd[MAXPATHLEN];
	t_env	*tmp;
	int		i;
	
	i = 0;
	g_cmd_ret = 0;
	tmp = NULL;
	if (!getcwd(oldpwd, MAXPATHLEN))
		return (print_err("getcwd() error", errno));
	if (!cmd_arg[1])
	{
		if (to_home() != 0)
			return (1);
	}
	else
	{
		if (cmd_arg[2] != NULL)
			return (print_err("cd : too many arguments", 1));
		if (cmd_arg[1][i] == '-')
		{
			tmp = find_env_var(env, "OLDPWD"); // faire attention à la possibilité qu'il n'y ai pas de variable OLDPWD !!
			ft_putendl_fd(tmp->value, fd);
			g_cmd_ret = chdir(tmp->value);
		}
		else
		{
			if (cmd_arg[1][i] == '~')
			{
				if (to_home() != 0)
					return (1);
				i = 2;
			}
			if (cmd_arg[1][i])
				g_cmd_ret = chdir(&cmd_arg[1][i]);
			if (g_cmd_ret == -1)
				return (print_err("No such file or directory", 1));
		}
	}
	if (change_pwd_oldpwd(oldpwd, env) != 0)
		return (1);
	return (0);
}
