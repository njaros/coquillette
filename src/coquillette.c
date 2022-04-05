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
		line_read = dollar_searcher(rl_get(line_read));
		if (line_read)
			execution(line_read, env_list);
		/*else
		{
			cmd_arg = ft_split(line_read, ' ');
			cmd = get_cmd(cmd_arg[0], path);
			if (cmd == NULL)
				printf("%s: command not found\n", cmd_arg[0]);
			else
				pid = fork();
				if (pid == -1)
					perror("fork");
				if (pid == 0)
					if (execve(cmd, cmd_arg, envp) == -1)
						perror("execve");
				waitpid(pid, NULL, 0);
		}*/
	}
	return (0);
}
