/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:45:10 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/28 14:29:53 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	built_exit(char **cmd_arg)
{
	int	i;

	if (cmd_arg[2])
	{
		ft_putendl_fd("exit : too many arguments", 2);
		g_cmd_ret = 1;
	}
	if (cmd_arg[1])
	{
		i = 0;
		while (cmd_arg[1][i])
		{
			if (!ft_isdigit(cmd_arg[1][i]))
			{
				ft_putendl_fd("numeric argument required", 2);
				g_cmd_ret = 255;
				break ;
			}
			i++;
		}
		if (g_cmd_ret != 255)
			g_cmd_ret = ft_atoi(cmd_arg[1]);
	}
	// fonction feel_free
	ft_putendl_fd("exit", 2);
	exit(g_cmd_ret);
}

// créer une fonctio qui vérifie la validité du nombre entré => atoi overflow ? sinon 255, seulement un - ou un +
// pas de + ou - tout seul...
// - ou + avec un espace avant le nb et - 42 devient 42 ?!
