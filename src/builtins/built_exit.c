/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:45:10 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/30 15:13:09 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+')
			return (1);
		if (arg[i + 1] == '-' || arg[i + 1] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	built_exit(char **cmd_arg)
{
	g_cmd_ret = 0;
	if (cmd_arg[1])
	{
		if (cmd_arg[2] != NULL)
		{
			ft_putendl_fd("exit : too many arguments", 2);
			g_cmd_ret = 1;
		}
		if (check_arg(cmd_arg[1]))
		{
			ft_putendl_fd("numeric argument required", 2);
			g_cmd_ret = 255;
		}
		if (!g_cmd_ret)
			g_cmd_ret = ft_atol(cmd_arg[1]);
	}
	// fonction feel_free
	ft_putendl_fd("exit", 2);
	exit(g_cmd_ret);
}
