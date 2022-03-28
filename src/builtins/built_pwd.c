/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:09:38 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/28 16:52:51 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	built_pwd(char **cmd_arg, int fd)
{
	char	pwd[MAXPATHLEN];

	g_cmd_ret = 0;
	if (!getcwd(pwd, MAXPATHLEN))
		return (print_err("getcwd() error", errno));
	ft_putendl_fd(pwd, fd);
	return (0);
}
