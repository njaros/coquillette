/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:45:10 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/28 11:21:46 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	built_exit(char **cmd_arg)
{
	int	i;

	g_cmd_ret = 0;
	if (!cmd_arg[1])
	{
		ft_putendl_fd("exit", 2);
		// fonction feel_free
	//	exit(cmd_ret); // code erreur enregsitré dans struct globale
	}
	if (cmd_arg[2])
	{
		ft_putendl_fd("exit : too many arguments", 2);
	//	cmd_ret = 1;
	}
	else
	{
		i = 0;
		while (cmd_arg[1][i])
		{
			if (!ft_isdigit(cmd_arg[1][i]))
			{
				ft_putendl_fd("numeric argument required", 2);
				//cmd_ret = 1;
				exit(128); // Invalid argument to exit
			}
			if (ft_atoi(cmd_arg[1]) < 0 || ft_atoi(cmd_arg[1]) > 255)
			{
				ft_putendl_fd("enter error code", 2);
				//cmd_ret = 1;
				exit(255); // Exit status out of range
			}
			else
				i++;
		}
		ft_putendl_fd("exit", 2);
		// fonction feel_free
		exit(ft_atoi(cmd_arg[1]));
	}
}
