/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:47:16 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/26 13:56:40 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	recover_status(t_data *data, pid_t *f_pid)
{
	int	j;
	int	status;

	j = 0;
	while (j < data->nb_cmd)
	{
		waitpid(f_pid[j], &status, 0);
		j++;
	}
	if (WIFEXITED(status))
		data->last_return = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		data->last_return = 130;
	free(f_pid);
}

void	child(t_data *data, int pipefd[2])
{
	char	*cmd_path;
	char	**envp;

	envp = list_to_tab(data->env);
	if (data->in != 0 && data->in != -1)
		if (dup2(data->in, STDIN_FILENO) == -1)
			error("exec: child: dup2 in");
	if (data->nb_cmd != 1)
		if (close(pipefd[0]) == -1)
			error("exec: child: close pipefd[0]");
	if (data->out != 1 && data->out != -1)
		if (dup2(data->out, STDOUT_FILENO) == -1)
			error("exec: child: dup2 out");
	if (data->in != -1 && data->out != -1)
	{
		if (do_builtins(data) == -1)
		{
			cmd_path = found_cmd(data, data->argv[0], data->env);
			if (!cmd_path || data->argv[0][0] == '\0')
				exit(data->last_return);
			if (execve(cmd_path, data->argv, envp) != 0)
				error("exec: child: execve");
		}
	}
	exit(data->last_return);
}

int	create_process(t_data *data, int pipefd[2], int *fd_in, int j)
{
	pid_t	f_pid;

	transform_fds(data, *fd_in, pipefd[1]);
	f_pid = fork();
	if (f_pid == -1)
		error("exec: create_process: fork");
	if (f_pid == 0)
		child(data, pipefd);
	if (j < data->nb_cmd - 1)
		if (close(pipefd[1]) == -1)
			error("exec: create_process: close pipefd[1]");
	if (data->in != 0 && data->in != -1)
		if (close(data->in) == -1)
			error("exec: create_process: close in");
	if (data->out != 1 && data->out != pipefd[1] && data->out != -1)
		if (close(data->out) == -1)
			error("exec: create_process: close out");
	*fd_in = pipefd[0];
	return (f_pid);
}

pid_t	*exec_cmd(t_data *data, char *line_read, int *i)
{
	int		j;
	int		pipefd[2];
	int		tmp_fd;
	pid_t	*f_pid;

	j = 0;
	tmp_fd = 3;
	f_pid = malloc(sizeof(int) * data->nb_cmd);
	if (!f_pid)
		error("exec: exec_cmd: f_pid");
	while (j < data->nb_cmd)
	{
		if (j < data->nb_cmd - 1)
			if (pipe(pipefd) == -1)
				error("exec: exec_cmd: pipe");
		f_pid[j] = create_process(data, pipefd, &tmp_fd, j);
		if (j < data->nb_cmd - 1)
			analyse(line_read, i, data);
		j++;
	}
	if (data->nb_cmd != 1)
		close(tmp_fd);
	return (f_pid);
}

void	execution(char *line_read, t_data *data)
{
	int		i;
	pid_t	*f_pid;

	i = 0;
	analyse(line_read, &i, data);
	if (data->out == -1 || data->in == -1)
		data->last_return = 1;
	if (data->argv)
	{
		if (!(check_is_builtin(data) != -1 && data->nb_cmd == 1))
		{
			f_pid = exec_cmd(data, line_read, &i);
			recover_status(data, f_pid);
		}
		else
			do_builtins(data);
	}
}
