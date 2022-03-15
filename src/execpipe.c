/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 08:43:38 by njaros            #+#    #+#             */
/*   Updated: 2022/03/15 09:42:26 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	execpipe(pipex_data *data)
{
	pid_t	fork_pid;

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
		if (execve(data->cmd_path, data->cmd, data->envp) == -1)
			return (error(-1));
	}
	
}