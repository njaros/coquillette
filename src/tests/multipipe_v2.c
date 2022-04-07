/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:28:45 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/05 15:40:29 by ccartet          ###   ########.fr       */
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
	else
		dup2(data->out, STDOUT_FILENO);
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
				exit(-1);
		}
		waitpid(f_pid, NULL, 0);
	}
	close(pipefd[1]);
	ft_free(envp);
	dprintf(2, "test");
	//return (pipefd[0]);
}


void	execution(char *line_read, t_list *env)
{
	t_data	data;
	int		i;
	int		pip;
	int		pipefd[2];
	int 	fd;
	
	i = 0;
	fd = 0;
	pip = analyse(line_read, &i, &data);
	dprintf(2, "%s\n", data.argv[0]);
	while (pip) // tant que analyse renvoit 1, c'est qu'il y a un pipe après la cmd
	{
		if (pipe(pipefd) == -1)
			error("pipe");
		pipe_test(&data, env, pipefd, pip);
		fd = pipefd[0];
		dup2(fd, STDIN_FILENO);
		//dprintf(2, "%d, %d\n", fd, STDIN_FILENO);
		pip = analyse(line_read, &i, &data);
	}
	pipe_test(&data, env, pipefd, pip);
	dprintf(2, "test2");
}