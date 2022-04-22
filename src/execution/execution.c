/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:47:16 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/22 14:47:14 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	do_builtins(t_data *data)
{
	if (!ft_strcmp(data->argv[0], "echo"))
		return (built_echo(data));
	else if (!ft_strcmp(data->argv[0], "cd"))
		return (built_cd(data));
	else if (!ft_strcmp(data->argv[0], "pwd"))
		return (built_pwd(data));
	else if (!ft_strcmp(data->argv[0], "export"))
		return (built_export(data));
	else if (!ft_strcmp(data->argv[0], "unset"))
		return (built_unset(data));
	else if (!ft_strcmp(data->argv[0], "env"))
		return (built_env(data));
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd == 1)
		return (built_exit(data));
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd != 1)
		return (0);
	return (-1);
}

void	child(t_data *data, int pipefd[2])
{
	char	*cmd_path;
	char	**envp;

	cmd_path = NULL;
	envp = list_to_tab(data->env);
	if (data->in != 0)
		if (dup2(data->in, STDIN_FILENO) == -1)
			error("dup2 in");
	if (data->nb_cmd != 1)
		if (close(pipefd[0]) == -1)
			error("close pipefd[0]");
	if (data->out != 1)
		if (dup2(data->out, STDOUT_FILENO) == -1)
			error("dup2 out");
	if (data->in != -1 && data->out != -1)
	{
		if (do_builtins(data) == -1)
		{
			cmd_path = found_cmd(data, data->argv[0], data->env);
			if (!cmd_path || data->argv[0][0] == '\0')
				exit(data->last_return);
			if (execve(cmd_path, data->argv, envp) != 0)
				error("execve");
		}
	}
	exit(data->last_return);
}

int	create_process(t_data *data, int pipefd[2], int *fd_in)
{
	pid_t	f_pid;

	transform_fds(data, *fd_in, pipefd[1]);
	// dprintf(2, "%s, %d, %d\n", data->argv[0], data->in, data->out);
	// dprintf(2, "%d, %d\n", pipefd[1], pipefd[0]);
	f_pid = fork();
	if (f_pid == -1)
		error("fork");
	if (f_pid == 0)
		child(data, pipefd);
	if (data->nb_cmd != 1)
		if (close(pipefd[1]) == -1)
			error("close pipefd[1]");
	if (data->in != 0)
		if (close(data->in) == -1)
			error("close in");
	if (data->out != 1 && data->out != pipefd[1])
		if (close(data->out) == -1)
			error("close out");
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
		error("malloc");
	while (j < data->nb_cmd && data->argv)
	{
		if (j < data->nb_cmd - 1)
			if (pipe(pipefd) == -1)
				error("pipe");
		f_pid[j] = create_process(data, pipefd, &tmp_fd);
		if (j < data->nb_cmd - 1)
			analyse(line_read, i, data);
		j++;
	}
	close(tmp_fd);
	return (f_pid);
}

void	execution(char *line_read, t_data *data)
{
	int		i;
	pid_t	*f_pid;
	int		j;
	int		status;

	i = 0;
	analyse(line_read, &i, data);
	if (!(check_is_builtin(data) != -1 && data->nb_cmd == 1))
	{
		f_pid = exec_cmd(data, line_read, &i);
		j = 0;
		while (j < data->nb_cmd)
		{
			waitpid(f_pid[j], &status, 0);
			j++;
		}
		if (WIFEXITED(status)) // si le child s'est terminé par un exit
			data->last_return = WEXITSTATUS(status);
		if (WIFSIGNALED(status)) // si le child s'est terminé grâce à un signal
			data->last_return = 130;
		free(f_pid);
	}
	else
		do_builtins(data);
}
