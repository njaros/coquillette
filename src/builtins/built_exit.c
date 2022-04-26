/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:45:10 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/26 13:54:47 by ccartet          ###   ########.fr       */
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
		if (!ft_isdigit(arg[i]) && arg[i] != '-'
			&& arg[i] != '+' && arg[i] != ' ')
			return (1);
		if ((arg[i] == '-' && arg[i + 1] == '\0')
			|| (arg[i] == '+' && arg[i + 1] == '\0'))
			return (1);
		if (arg[i] == '-' || arg[i] == '+')
			sign = 1;
		if (sign == 1 && (arg[i + 1] == '-' || arg[i + 1] == '+'))
			return (1);
		i++;
	}
	return (0);
}

void	exit_minishell(t_data *data)
{
	feel_free(data->env);
	ft_lstclear(&(data->env), del);
	ft_free(data->argv);
	terminal_handler(1);
	exit(data->last_return);
}

int	built_exit(t_data *data)
{
	long long	num;
	int			check;

	num = 0;
	check = 0;
	if (data->nb_cmd == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (data->argv[1])
	{
		check = ft_atol(data->argv[1], &num);
		if (check_arg(data->argv[1]) || check == 1)
			print_error(data, data->argv[1], "numeric argument required", 255);
		else if (data->argv[2] != NULL)
		{
			print_error(data, NULL, "too many arguments", 1);
			return (1);
		}
		else
			data->last_return = num;
	}
	if (data->nb_cmd == 1)
		exit_minishell(data);
	return (0);
}
