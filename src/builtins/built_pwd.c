/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:09:38 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/21 16:17:32 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	built_pwd(t_data *data)
{
	char	pwd[MAXPATHLEN];
	t_env	*tmp;

	data->last_return = 0;
	kill(0, SIGUSR1);
	if (data->out == -1)
	{
		data->last_return = 1;
		exit(data->last_return);
	}
	if (!getcwd(pwd, MAXPATHLEN))
	{
		tmp = find_env_var(env, "PWD");
		ft_putendl_fd(tmp->value, data->out);
	}
	else
		ft_putendl_fd(pwd, data->out);
	exit(data->last_return);
}

// attention vérifier erreur d'ecriture permission denied