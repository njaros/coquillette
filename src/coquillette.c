/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coquillette.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:47:13 by njaros            #+#    #+#             */
/*   Updated: 2022/03/08 16:57:51 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	act;
	char				*line_read;
	t_list				*env_list;
	t_data				data;

	(void)argc;
	(void)argv;
	env_list = init_envp(envp);
	if (!env_list)
		error("malloc");
	init(&act, &data, env_list);
	kill(0, SIGUSR2);
	line_read = NULL;
	while (1)
	{
		line_read = rl_get(line_read, &data);
		if (line_read)
			execution(line_read, &data);
	}
	ft_lstclear(&env_list, feel_free);
	return (0);
}
