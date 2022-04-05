/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:28:45 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/05 14:46:56 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	pipe_test(t_data *data, t_list *env, int pipefd[2], int pip)
{
	pid_t	f_pid;
	char	**envp;

	envp = transform_list(env);
	close(pipefd[0]);
	if (pip)
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
			if (execve(data->cmd_path, data->argv, envp) == -1)
				exit (-1);
		}
		waitpid(f_pid, NULL, 0);
	}
	dprintf(2, "blop\n");
	close(pipefd[1]);
	if (pip)
		dup2(pipefd[0], STDIN_FILENO);
	ft_free(envp);
}


void	execution(char *line_read, t_list *env)
{
	t_data	data;
	int		i;
	int		pip;
	int		pipefd[2];
	
	i = 0;
	if (pipe(pipefd) == -1)
		error("pipe");
	pip = analyse(line_read, &i, &data);
	while (pip) // tant que analyse renvoit 1, c'est qu'il y a un pipe après la cmd
	{
		pipe_test(&data, env, pipefd, pip);
		pip = analyse(line_read, &i, &data);
	}
	pipe_test(&data, env, pipefd, pip);
}