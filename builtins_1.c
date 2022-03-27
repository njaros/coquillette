/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:42:30 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/27 16:58:51 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coquillette.h"

void	builtins(char **cmd_arg)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		built_echo(cmd_arg, fd);
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		built_cd(cmd_arg, env);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		built_pwd(fd);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		built_export(cmd_arg, fd);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		built_unset(cmd_arg, env);
	else if (!ft_strcmp(cmd_arg[0], "env"))
		built_env(env, fd);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		built_exit(cmd_arg, fd);
}

void	built_echo(char **cmd_arg, int fd)
{
	int		nl;
	int		i;
	char	*new;

	nl = 1;
	i = 1;
	if (!ft_strncmp(cmd_arg[i], "-n", 2)) // vérifier si après - on a bien un n
	{
		n = 0;
		i++;
	}
	new = dollar_searcher(cmd_arg[i]);
	ft_putstr_fd(new, fd);
	if (nl)
		ft_putchar_fd('\n', fd);
} // vérifier si echo s'arrete bien quand il y a un espace, qu'est ce qu'il fait s'il y a un \n
// sinon while avec putchar espace
void	built_export(char **cmd_arg, t_list *env)
{
	t_env	*tmp;
	t_list	*new;
	int		ok;
 // vérifier si l'arguement entré est valable, s'il y a un =, que fait export NAME (sans =, sans rien après) ?
	// attention possibilité de créer plusieurs variables en même temps !!
	ok = 0;
	while (env) // créer fonction qui recherche la variable d'environnement !!
	{
		tmp = env->content;
		if (!ft_strncmp(cmd_arg[1], tmp->name, ft_strlen(tmp->name)))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_substr(ft_strchr(cmd_arg[1], '='), 1, ft_strlen(cmd_arg[1]));
			ok = 1;
		}
		env = env->next;
	}
	if (!ok)
	{
		new = ft_lstnew(create_struct(cmd_arg[1]));
		if (!new)
			return (NULL);
		ft_lstadd_back(&env, new);
	}
} // que fait export tout court ?!

void	built_unset(char **cmd_arg, t_list *env) // méthode faignasse
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->content;
		if (!ft_strncmp(cmd_arg[1], tmp->name, ft_strlen(tmp->name)))
		{
			free(tmp->value);
			tmp->value = NULL;
			return ;
		}
		env = env->next;
	}
}
