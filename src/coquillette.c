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

int	main(int argc, char ** argv, char **envp)
{
	struct sigaction	act;
	char				*line_read;
	t_list				*env_list;
	int					cmd_return;
	t_data				data;

	(void)argc;
	cmd_return = 0;
	env_list = init_envp(envp);
	if (!env_list)
		return (1);
	init(&act, &data, env_list);
	kill(0, SIGUSR2);
	line_read = NULL;
	while (1)
	{
		line_read = rl_get(line_read, &cmd_return);
		if (line_read)
			cmd_return = execution(line_read, &data);
	}
	feel_free(env_list);
	ft_lstclear(&env_list, del);
	return (0);
}
