/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 08:43:38 by njaros            #+#    #+#             */
/*   Updated: 2022/03/15 15:37:27 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	ft_switch(int n)
{
	if (n)
		return (0);
	return (1);
}

int	parsing_line(char *line, pipex_data *data, int *begin)
{
	int		i;
	int		in_quote;
	char	*who_s_cmd;
	int		who_s_fd_rd;
	int		who_s_fd_wr;

	in_quote = 0;
	i = -1;
	while (line[++i] && !(line[i] == ' ' && in_quote == 1))
	{
		if (line[i] == 34) // 34 = "
			in_quote = ft_switch(in_quote);
	}
	if (line[i] == ' ')
		who_s_cmd = found_cmd(ft_substr(line, 0, i), data->envp);
}

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

int	execpipe(pipex_data *data)
{
	pid_t	fork_pid;
	int		err;

	err = 0;
	fork_pid = fork();
	if (fork_pid == -1)
		return (error(-1));
	if (fork_pid == 0)
	{
		if (dup2(data->pipefd_in[0], STDIN_FILENO) == -1)
			return (error(-1));
		if (dup2(data->pipefd_out[1], STDOUT_FILENO) == -1)
			return (error(-1));
		close(data->pipefd_out[0]);
		close(data->pipefd_in[1]);
		err = execve(data->cmd_path, data->cmd, data->envp);
		return (err);
	}
	close(data->pipefd_in[0]);
	close(data->pipefd_out[1]);
	waitpid(fork_pid, NULL, 0);
	return (err);
}