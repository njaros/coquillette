/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:37:27 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/21 16:17:18 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

static void	print(t_data *data, t_env *tmp)
{
	ft_putstr_fd(tmp->name, data->out);
	ft_putchar_fd('=', data->out);
	ft_putendl_fd(tmp->value, data->out);
}

void	built_env(t_data *data)
{
	t_env	*tmp;

	data->last_return = 0;
	kill(0, SIGUSR1);
	if (data->out == -1)
		data->last_return = 1;
	else if (data->argv[1] != NULL)
	{
		data->last_return = 127;
		print_error(data->argv[0], "too many arguments");
	}
	else
	{
		while (data->env)
		{
			tmp = data->env->content;
			if (tmp->eg == '=')
				print(data, tmp);
			data->env = data->env->next;
		}	
	}
	exit(data->last_return);
}
