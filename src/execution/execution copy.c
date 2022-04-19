/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:47:16 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/19 15:01:37 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	transform_fds(t_data *data, int fd_in, int fd_out)
{
	if (data->in == -2) // sauf premiere cmd
	// je lui passe le fd_in récupéré du précédemment passage : pipefd[0]
		data->in = fd_in;
	if (data->out == -2) // sauf derniere cmd
		data->out = fd_out;
}

int	fork_loop(t_data *data, int pipefd[2], int *fd_in)
{
	pid_t	f_pid;
	char	**envp;
	char	*cmd_path;

	envp = list_to_tab(data->env);
	cmd_path = NULL;
	transform_fds(data, *fd_in, pipefd[1]);
	dprintf(2, "%s, %d, %d\n", data->argv[0], data->in, data->out);
	f_pid = fork();
	if (f_pid == -1)
		perror("fork");
	if (f_pid == 0)
	{
		if (data->in != 0)
			dup2(data->in, STDIN_FILENO);
		close(pipefd[0]);
		if (data->out != 1)
			dup2(data->out, STDOUT_FILENO);
		if (data->in != -1 && data->out != -1)
		{
			if (builtins(data) == -1)
			{
				cmd_path = found_cmd(data->argv[0], data->env);
				if (!cmd_path || data->argv[0][0] == '\0')
				{
					ft_putstr_fd("coquillette: ", 2);
					ft_putstr_fd(data->argv[0], 2);
					ft_putendl_fd(": command not found", 2);
					exit(1);
				}
				if (execve(cmd_path, data->argv, envp) != 0)
					error("execve");
			}
		}
		exit(0);
	}
	close(pipefd[1]);
	if (data->in != 0)
		close(data->in);
	if (data->out != 1)
		close(data->out);
	ft_free(envp);
	free(cmd_path);
	*fd_in = pipefd[0];
	return (f_pid);
}

int	builtins(t_data *data)
{
	if (!ft_strcmp(data->argv[0], "echo"))
		return (built_echo(data->argv, data->out));
	else if (!ft_strcmp(data->argv[0], "cd"))
		return (built_cd(data->argv, data->env, data->out));
	else if (!ft_strcmp(data->argv[0], "pwd"))
		return (built_pwd(data->argv, data->out));
	else if (!ft_strcmp(data->argv[0], "export"))
		return (built_export(data->argv, data->env, data->out));
	else if (!ft_strcmp(data->argv[0], "unset"))
		return (built_unset(data->argv, data->env));
	else if (!ft_strcmp(data->argv[0], "env"))
		return (built_env(data->env, data->argv, data->out));
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd == 1)
		built_exit(data);
	else if (!ft_strcmp(data->argv[0], "exit") && data->nb_cmd != 1)
		return (0);
	return (-1);
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
	while (j < data->nb_cmd - 1 && data->argv)
	{
		if (pipe(pipefd) == -1)
			error("pipe");
		f_pid[j] = fork_loop(data, pipefd, &tmp_fd);
		ft_free(data->argv);
		analyse(line_read, i, data);
		j++;
	}
	if (data->argv)
	{
		if (builtins(data) == -1)
			f_pid[j] = fork_loop(data, pipefd, &tmp_fd);
		close(tmp_fd);
		ft_free(data->argv);
	}
	return (f_pid);
}

int	execution(char *line_read, t_data *data)
{
	int		i;
	pid_t	*f_pid;
	int		j;

	i = 0;
	analyse(line_read, &i, data);
	f_pid = exec_cmd(data, line_read, &i);
	j = 0;
	while (j < data->nb_cmd)
	{
		waitpid(f_pid[j], &data->last_return, 0);
		j++;
	}
	free(f_pid);
	return (data->last_return);
}
