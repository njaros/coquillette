/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:17:08 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/27 18:01:38 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// int	init_rank(char **envp, int i)
// {
// 	int	rank;
// 	int	a;

// 	rank = 1;
// 	a = 0;
// 	while (envp[a])
// 	{
// 		if (envp[i][0] > envp[a][0])
// 			rank++;
// 		a++;
// 	}
// 	return (rank);
// }

// int	*sort_env(t_list *env) // transformer ma liste chainée en tableau trié
// {
// 	t_env	*tmp;
// 	int		*tab; // comment savoir la taille de ma liste ?

// 	// en cours...
// }

void	print_export(t_list *env, int fd)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env->content;
		if (tmp->value)
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
		}
		env = env->next;
	}
}
// attention trier par ordre alphabétique !!

void	built_export(char **cmd_arg, t_list *env, int fd)
{
	int		i;
	t_env	*tmp;
	char	*to_search;
	char	*value;

	i = 1;
	if (!cmd_arg[1])
		print_export(env, fd);
	while (cmd_arg[i])
	{
		if (!ft_strrchr(cmd_arg[i], '=')) // tester ce qu'il se passe si on a un = dès la premiere lettre..., possibilité qu'il y ai des chiffres ?!
		{
			ft_putendl_fd("variable is not valid", 2);
			//cmd_ret = 1;
			return ;
		}
		to_search = ft_substr(cmd_arg[i], 0, ft_strchr(cmd_arg[i], '=') - cmd_arg[i]);
		tmp = find_env_var(env, to_search);
		free(to_search);
		value = ft_substr(ft_strchr(cmd_arg[i], '='), 1, ft_strlen(cmd_arg[i])); // vérifier comportement si rien après le =, \0 ??
		replace_or_create(env, tmp, cmd_arg[i], value);
		i++;
	}
}
// attention ! tester export NAME=, et ensuite env, je dois voir cette nouvelle variable apparaitre