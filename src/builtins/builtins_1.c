/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:42:30 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/15 14:48:03 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coquillette.h"


void	builtins(char **cmd_arg)
{
	if (!ft_strncmp(cmd_arg[0], "echo", 4))
		built_echo
	else if (!ft_strncmp(cmd_arg[0], "cd", 2))
		built_cd(cmd_arg);
	else if (!ft_strncmp(cmd_arg[0], "pwd", 3))
		built_pwd();
	else if (!ft_strncmp(cmd_arg[0], "export", 6))
		built_export
	else if (!ft_strncmp(cmd_arg[0], "unset", 5))
		built_unset
	else if (!ft_strncmp(cmd_arg[0], "env", 3))
		built_env(env, fd);
	else if (!ft_strncmp(cmd_arg[0], "exit", 4))
		built_exit(cmd_arg);
}

void	built_echo(char **cmd_arg)
{

	if (!ft_strncmp(cmd_arg[1], "-n", 2)) // modifier varaibale option
	//	affichage sans \n + checker si c'est bien un n après le tiret...


}

void	built_cd(char **cmd_arg, t_list *env)
{
	char	*home;
	t_env	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	home = getenv("HOME"); // vérifier à chaque appel de cette fonction que la varibale existe, sinon la créer ??
	if (!cmd_arg[1])
		chdir(home);
	else
	{
		if (!ft_strncmp(cmd_arg[1], "~", 1))
			chdir(home);
		else if (chdir(cmd_arg[1]) == -1)
			perror("cd");
	}
	while (env)
	{
		tmp = env->content;
		if (!ft_strncmp(tmp->name, "PWD", 3))
			tmp->value = getcwd(NULL, 0);
		if (!ft_strncmp(tmp->name, "OLDPWD", 3))
			tmp->value = pwd;
		env = env->next;
	}
}

void	built_pwd(int fd)
{
	char	*pwd;

	// if (getcwd(pwd, sizeof(pwd) == NULL)
	// 	perror("getcwd() error");
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
}

void	built_env(t_list *env, int fd)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->content;
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putchar_fd('\n', fd); // le fd peut etre différent de la sortie standard !!!!
		}
		env = env->next;
	}
}

void	built_exit(char **cmd_arg, int fd)
{
	int	i;

	if (!cmd_arg[1])
	{
		ft_putstr_fd("exit", fd);
		ft_putchar_fd('\n', fd);
		exit(code_erreur); // code erreur enregsitré dans struct globale + free
	}
	else // verifier aussi sir le nb est compris entre 0 et ..., si c'est un code erreur
	{
		i = 0;
		while(cmd_arg[1][i])
		{
			if (ft_isdigit(cmd_arg[1][i]))
				i++;
			else
				return ;
		}
		ft_putstr_fd("exit", fd);
		ft_putchar_fd('\n', fd);
		exit(ft_atoi(cmd_arg[1])); // + free
	}
}