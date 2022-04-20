/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:37:27 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/07 14:35:12 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	built_env(t_list *env, char **cmd_arg, int fd)
{
	t_env	*tmp;

	g_cmd_ret = 0;
	kill(0, SIGUSR1);
	if (cmd_arg[1] != NULL)
		return (print_err("env : too many arguments", 1));
	while (env)
	{
		tmp = env->content;
		if (tmp->eg == '=')
		{
			ft_putstr_fd(tmp->name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(tmp->value, fd);
		}
		env = env->next;
	}
	return (0);
}
