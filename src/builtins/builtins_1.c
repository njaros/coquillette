/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:42:30 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/24 11:18:25 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coquillette.h"

int	ft_strcmp(char *s1, char *s2)
{
    int	i;

    i = 0;
    while (s1[i] || s2[i])
    {
        if (!(s1[i] == s2[i]))
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (0);
}

void	builtins(char **cmd_arg)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		built_echo
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		built_cd(cmd_arg, env);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		built_pwd(fd);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		built_export
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		built_unset
	else if (!ft_strcmp(cmd_arg[0], "env"))
		built_env(env, fd);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		built_exit(cmd_arg, fd);
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
		if (!ft_strcmp(cmd_arg[1], "~"))
			chdir(home);
		else if (chdir(cmd_arg[1]) == -1)
			perror("cd");
	}
	while (env)
	{
		tmp = env->content;
		if (!ft_strcmp(tmp->name, "PWD"))
			tmp->value = getcwd(NULL, 0);
		if (!ft_strcmp(tmp->name, "OLDPWD"))
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