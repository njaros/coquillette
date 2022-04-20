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

void	built_exit(t_data *data)
{
	char	*level;
	int		lvl;
	t_env	*tmp;
	char	*var_name;
	
	g_cmd_ret = 0;
	kill(0, SIGUSR1);
	level = getenv("SHLVL"); // modification du level shell, attention que ce passe-t-il s'il n'y a pas de variable SHLVL ?
	lvl = ft_atoi(level); // créer une sous-fonction
	lvl--;
	level = ft_itoa(lvl);
	tmp = find_env_var(data->env, "SHLVL");
	var_name = ft_strjoin("SHLVL=", level);
	replace_or_create(data->env, tmp, var_name, level);
	free(level);
	free(var_name);
	if (data->argv[1])
	{
		if (data->argv[2] != NULL)
		{
			ft_putendl_fd("exit : too many arguments", 2);
			g_cmd_ret = 1;
		}
		if (check_arg(data->argv[1]))
		{
			ft_putendl_fd("numeric argument required", 2);
			g_cmd_ret = 255;
		}
		if (!g_cmd_ret)
			g_cmd_ret = ft_atol(data->argv[1]);
	}
	feel_free(data->env);
	ft_lstclear(&(data->env), del);
	ft_putendl_fd("exit", 2);
	terminal_handler(1);
	exit(g_cmd_ret);
}
