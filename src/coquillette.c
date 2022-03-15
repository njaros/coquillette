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

int	init_envp(t_env **env, char **envp)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (-1);
		tmp->name = ft_substr(envp[0], 0, ft_strchr(envp[0], '=') - envp[0]);
		tmp->value = ft_substr(ft_strchr(envp[0], '='), 0, ft_strlen(envp[0])); // faire attention au cas où il n'y aurait pas de valeur !!
		tmp->next = NULL;
		ft_lstadd_back(env, tmp); // attention arguments à transformer en t_env
		free(tmp);
		i++;
	}
}

int	main(int argc, char ** argv, char **envp)
{
	struct sigaction	act;
	char				*line_read;
	(void)argc;
	char   				*env;
	char				**path;
	char				**cmd_arg;
	char				*cmd;
	pid_t				pid;
	pipex_data			data;

	init_sigact(&act);
	init_pipex_data(&data, envp);
	env = getenv("PATH");
	path = ft_split(env, ':');
	line_read = NULL;
	while (1)
	{
		line_read = rl_get(line_read);
		while (contain_pipe(line_read))
		{
			parsing_line(&line_read, &data);
			execpipe(data);
		}
		else
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
		}
	}
	return (0);
}
