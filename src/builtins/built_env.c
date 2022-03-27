/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:37:27 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/27 17:58:31 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	built_env(t_list *env, char **cmd_arg, int fd)
{
	t_env	*tmp;

	if (cmd_arg[1] != NULL)
	{
		ft_putendl_fd("env : too many arguments", 2);
		//cmd_ret = 1;
		return ;
	}
	while (env)
	{
		tmp = env->content;
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(tmp->value, fd);
		}
		env = env->next;
	}
}
