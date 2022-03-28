/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:58:18 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/28 11:38:44 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	built_echo(char **cmd_arg, int fd)
{
	int		nl;
	int		i;
	char	*new;

	nl = 1;
	i = 1;
	g_cmd_ret = 0;
	if (cmd_arg[i][0] == '-' && cmd_arg[i][1] == 'n')
	{
		if (cmd_arg[i][1] == 'n')
			nl = 0;
		else
			return (print_err("echo : invalid option", 1));
		i++;
	}
	while (cmd_arg[i])
	{
		//new = dollar_searcher(cmd_arg[i]);
		ft_putstr_fd(cmd_arg[i], fd);
		if 
		ft_putchar_fd(' ', fd);
		//free(new);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', fd);
	return (0);
}
// echo ne s'arrete pas s'il trouve un espace !!