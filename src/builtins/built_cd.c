/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:15:00 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/27 18:06:33 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	replace_or_create(t_list *env, t_env *var, char *var_name, char *path)
{
	t_list	*new;

	new = NULL;
	if (!var)
	{
		new = ft_lstnew(create_struct(var_name));
		if (!new)
			//cmd_ret = 1;
		ft_lstadd_back(&env, new);
	}
	else
	{
		if (var->value) // pas focrément utile...
			free(var->value);
		var->value = path;
	}
}

void	change_pwd_oldpwd(char *oldpwd, t_list *env)
{
	t_env	*tmp;
	t_list	*new;
	char	pwd[MAXPATHLEN];
	char	*var_name;

	if (!getcwd(pwd, MAXPATHLEN))
	{
		ft_putendl_fd("getcwd() error", 2);
		//cmd_ret = errno;
	}
	tmp = find_env_var(env, "PWD");
	var_name = ft_strjoin("PWD=", pwd);
	replace_or_create(env, tmp, var_name, pwd);
	free(var_name);
	tmp = find_env_var(env, "OLDPWD");
	var_name = ft_strjoin("OLDPWD=", oldpwd);
	replace_or_create(env, tmp, var_name, oldpwd);
	free(var_name);
	free(pwd);
	free(oldpwd);
}

void	to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		perror("cd : HOME not set");
		//cmd_ret = errno;
	}
	/*cmd_ret = */chdir(home);
}

void	built_cd(char **cmd_arg, t_list *env)
{
	char	oldpwd[MAXPATHLEN];

	if (cmd_arg[2] != NULL)
	{
		ft_putendl_fd("cd : too many arguments", 2);
		//cmd_ret = 1;
		return ;
	}
	if (!getcwd(oldpwd, MAXPATHLEN))
	{
		ft_putendl_fd("getcwd() error", 2);
		//cmd_ret = errno;
	}
	if (!cmd_arg[1])
		to_home();
	else
	{
		/*cmd_ret = */chdir(cmd_arg[1]);
		// if (cmd_ret == -1)
		// 	ft_putendl_fd(strerror(errno), 2);
	}
	change_pwd_oldpwd(oldpwd, env);
}

// coder "cd -" ??
// leaks à tester !!