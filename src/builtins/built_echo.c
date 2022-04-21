/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:58:18 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/21 16:17:09 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

static void	print(t_data *data, int i)
{
	ft_putstr_fd(data->argv[i], data->out);
	if (data->argv[i][0] && data->argv[i + 1])
		ft_putchar_fd(' ', data->out);
}

void	built_echo(t_data *data)
{
	int		nl;
	int		i;
	char	*new;

	data->last_return = 0;
	kill(0, SIGUSR1);
	if (data->out == -1)
	{
		data->last_return = 1;
		exit(data->last_return);
	}
	nl = 1;
	i = 1;
	while (data->argv[i])
	{
		if (data->argv[i][0] == '-' && data->argv[i][1] == 'n')
			nl = 0;
		else
			print(data, i);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', data->out);
	exit(data->last_return);
}
