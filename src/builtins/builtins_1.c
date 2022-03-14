/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:42:30 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/14 10:42:41 by ccartet          ###   ########.fr       */
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

void	build_env(t_env *env, int fd)
{
	while (env)
	{
		if (env->value) // vérifier s'il faut tout afficher sous bash ??
		{
			ft_putstr(env->name, fd);
			ft_putstr(env->value, fd);
			ft_putchar('\n', fd); // le fd peut etre différent de la sortie standard !!!!
			//printf("%s=%s\n", env->name, env->value); // OU
		}
		env->next;
	}
}

void	built_cd(char **cmd_arg)
{
	char	*home;

	if (!cmd_arg[1])
	{
		home = getenv("HOME"); // vérifier à chaque appel de cette fonction que la varibale existe, sinon la créer ??
		chdir(home);
	}
	else
	{
		if (chdir(cmd_arg[1]) == 1)
			perror("dir");
		else
		// modifier le pwd et le oldpwd
	}
}

void	built_pwd(void)
{
	char	pwd[256]; // max path len ?

	if (getcwd(pwd, sizeof(pwd) == NULL) // ou pwd = getcwd(NULL, 0);
		perror("getcwd() error");
	else
		printf("%s\n", pwd);
}

void	built_exit(char **cmd_arg)
{
	int	i;

	if (!cmd_arg[1])
		exit(code_erreur); // code erreur enregsitré dans struct globale + free
	else
	{
		i = 0;
		while(cmd_arg[1][i])
		{
			if (ft_isdigit(cmd_arg[1][i]))
				i++;
			else
				return ;
		}
		exit(ft_atoi(cmd_arg[1])); // + free
	}
}	