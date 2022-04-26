/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:09:38 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/26 14:17:39 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	built_pwd(t_data *data)
{
	char	pwd[MAXPATHLEN];
	t_env	*tmp;

	data->last_return = 0;
	if (data->out == -1 || data->in == -1)
	{
		data->last_return = 1;
		return (1);
	}
	if (!getcwd(pwd, MAXPATHLEN))
	{
		tmp = find_env_var(data->env, "PWD");
		ft_putendl_fd(tmp->value, data->out);
	}
	else
		ft_putendl_fd(pwd, data->out);
	return (0);
}

// attention vérifier erreur d'ecriture sur fichier permission denied