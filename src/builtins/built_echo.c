/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:58:18 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/28 11:45:06 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	built_echo(char **cmd_arg, int fd)
{
	int		nl;
	int		i;
	char	*new;

	nl = 1;
	i = 1;
	if (cmd_arg[i][0] == '-' && cmd_arg[i][1] == 'n')
	{
		nl = 0;
		i++;
	}
	while (cmd_arg[i])
	{
		//new = dollar_searcher(cmd_arg[i]);
		ft_putstr_fd(cmd_arg[i], fd);
		if (cmd_arg[i + 1])
			ft_putchar_fd(' ', fd);
		//free(new);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', fd);
}
