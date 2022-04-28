/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:09:38 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/27 11:36:59 by ccartet          ###   ########.fr       */
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
		if (!tmp)
		{
			print_error(data, NULL, "PWD not set", 1);
			return (1);	
		}
		ft_putendl_fd(tmp->value, data->out);
	}
	else
		ft_putendl_fd(pwd, data->out);
	return (0);
}

// attention vérifier erreur d'ecriture sur fichier permission denied