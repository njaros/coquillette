/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:09:38 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/27 17:56:48 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	built_pwd(char **cmd_arg, int fd)
{
	char	pwd[MAXPATHLEN];

	if (cmd_arg[1] != NULL)
	{
		ft_putendl_fd("pwd : too many arguments", 2);
		//cmd_ret = 1;
	}
	if (!getcwd(pwd, MAXPATHLEN))
	{
		ft_putendl_fd("getcwd() error", 2);
		//cmd_ret = errno;
	}
	ft_putendl_fd(pwd, fd);
}
