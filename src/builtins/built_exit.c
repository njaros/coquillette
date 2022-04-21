/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:45:10 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/19 11:27:45 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	check_arg(char *arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+' && arg[i] != ' ')
			return (1);
		if (arg[i] == '-' || arg[i] == '+')
			sign = 1;
		if (sign == 1 && (arg[i + 1] == '-' || arg[i + 1] == '+'))
			return (1);
		i++;
	}
	return (0);
}

void	built_exit(t_data *data, int *close)
{
	t_env	*tmp;
	char	*var_name;
	
	kill(0, SIGUSR1);
	if (data->argv[1])
	{
		if (check_arg(data->argv[1]))
		{
			print_error(data->argv[0], "numeric argument required");
			data->last_return = 255;
			exit(data->last_return);
		}
		if (data->argv[2] != NULL)
		{
			print_error(data->argv[0], "too many arguments");
			exit(EXIT_FAILURE);
		}
		data->last_return = ft_atol(data->argv[1]);
	}
	feel_free(data->env); // a intégrer dans une autre fonction hors du fork !!!
	ft_lstclear(&(data->env), del); // ok ?
	ft_putendl_fd("exit", STDERR_FILENO);
	terminal_handler(1);
	*close = 1;
	exit(data->last_return);
}
