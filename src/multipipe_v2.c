/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:28:45 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/05 12:06:07 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	pipe_test(t_data *data, t_list *env)
{
	int		pipedfd[2];
	pid_t	f_pid;
	char	**envp;

	if (pipe(pipefd) == -1)
		error("pipe");
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	// if (check_built == 1) // la cmd rentrée n'est pas un built-in, alors on crée un fork
	
	data->cmd_path = found_cmd(data->argv[0]);
	if (!data->cmd_path) // vérifier que la commande existe
		printf("%s: command not found\n", data->argv[0]);
	else
	{
		f_pid = fork();
		if (f_pid == -1)
			perror("fork");
		if (f_pid == 0)
		{
			envp = transform_list(env);
			if (execve(data->cmd_path, data->argv, envp) == -1)
				exit (-1);
		}
		ft_free(envp);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
}


void	execution(char *line_read, t_list *env)
{
	
	while (analyse(line_read, &i, &data)) // tan que analyse renvoit 1, c'est qu'il y a un pipe après la cmd
	{
		
	}
}