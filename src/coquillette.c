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
	(void)argc;
	t_list				*env_list;

	init_sigact(&act);
	env_list = init_envp(envp);
	if (!env_list)
		return (1);
	line_read = NULL;
	while (1)
	{
		line_read = rl_get(line_read);
		if (line_read)
			execution(line_read, env_list);
	}
	return (0);
}
