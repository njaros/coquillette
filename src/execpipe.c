/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 08:43:38 by njaros            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/30 11:57:42 by njaros           ###   ########lyon.fr   */
=======
/*   Updated: 2022/03/30 15:23:13 by ccartet          ###   ########.fr       */
>>>>>>> ec333adce60d4aaf4d9e31b01bf1a6522cee4ed1
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*found_cmd(char *entry)
{
	char	*env;
	char	*cmd;
	char	**path_tab;
	int		i;
	i = -1;
	while (entry[++i])
		if (entry[i] == '/')
			return (entry);
	env = getenv("PATH");
	path_tab = ft_split(env, ':');
	free(env);
	cmd = get_cmd(entry, path_tab);
	ft_free(path_tab);
	free(entry);
	return (cmd);
}

int	is_spechar(char c)
{
	if (c == ' ')
		return (1);
	if (c == '$')
		return (1);
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}
/*
char	*next_pipe(char *line, pipex_data *data)
{
	char	*next_cmd;
	if (data->next_pipe_pos == 0)
	{
		free(line);
		return (NULL);
	}
	next_cmd = ft_strdup(&line[data->next_pipe_pos + 1]);
	free(line);
	data->pipefd_in[0] = data->pipefd_out[0];
	data->pipefd_in[1] = data->pipefd_out[1];
	if (pipe(data->pipefd_out) == -1)
		return (NULL);
	return (next_cmd);
}


int	execpipe(t_data *data)
{
	pid_t	fork_pid;
	int		err;
	err = 0;
	fork_pid = fork();
	if (fork_pid == -1)
		return (error2(-1));
	if (fork_pid == 0)
	{
		if (dup2(data->pipefd_in[0], STDIN_FILENO) == -1)
			return (error2(-1));
		if (dup2(data->pipefd_out[1], STDOUT_FILENO) == -1)
			return (error2(-1));
		close(data->pipefd_out[0]);
		close(data->pipefd_in[1]);
		err = execve(data->path, data->argv, data->envp);
		return (err);
	}
	close(data->pipefd_in[0]);
	close(data->pipefd_out[1]);
	waitpid(fork_pid, NULL, 0);
	return (err);
}
<<<<<<< HEAD
void	exec()
{

}
void	test_multipipe()
{
	int		pip_nb;
	t_pipe	pip;
	int		fd[2];
	int		tmp_fd;
	pid_t	fork_pid;
=======
>>>>>>> ec333adce60d4aaf4d9e31b01bf1a6522cee4ed1

