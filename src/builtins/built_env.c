/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:37:27 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/22 15:15:44 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

static void	print_env(t_data *data, t_env *tmp)
{
	ft_putstr_fd(tmp->name, data->out);
	ft_putchar_fd('=', data->out);
	ft_putendl_fd(tmp->value, data->out);
}

int	built_env(t_data *data)
{
	t_env	*tmp;

	data->last_return = 0;
	if (data->out == -1)
		data->last_return = 1;
	else if (data->argv[1] != NULL)
		print_error(data, NULL, "too many arguments", 127);
	else
	{
		while (data->env)
		{
			tmp = data->env->content;
			if (tmp->eg == '=')
				print_env(data, tmp);
			data->env = data->env->next;
		}	
	}
	return (0);
}
