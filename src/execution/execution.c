/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:47:16 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/19 10:54:56 by ccartet          ###   ########.fr       */
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

int fork_loop(t_data *data, int pipefd[2], t_list *env, int *fd_in)
{
	pid_t	f_pid;
	char	**envp;
	char	*cmd_path;

	envp = list_to_tab(env);
	cmd_path = NULL;
	transform_fds(data, *fd_in, pipefd[1]);
	// dprintf(2, "%s, %d, %d\n", data->argv[0], data->in, data->out);
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
			if (builtins(*data, env) == -1)
			{
				cmd_path = found_cmd(data->argv[0], env);
				if (!cmd_path || data->argv[0][0] == '\0')
				{
					dprintf(2, "coquillette: %s: command not found\n", data->argv[0]);
					exit(1);
				}
				else if (execve(cmd_path, data->argv, envp) != 0)
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

int	builtins(t_data data, t_list *env)
{
	if (!ft_strcmp(data.argv[0], "echo"))
		return (built_echo(data.argv, data.out));
	else if (!ft_strcmp(data.argv[0], "cd"))
		return (built_cd(data.argv, env, data.out));
	else if (!ft_strcmp(data.argv[0], "pwd"))
		return (built_pwd(data.argv, data.out));
	else if (!ft_strcmp(data.argv[0], "export"))
		return (built_export(data.argv, env, data.out));
	else if (!ft_strcmp(data.argv[0], "unset"))
		return (built_unset(data.argv, env));
	else if (!ft_strcmp(data.argv[0], "env"))
		return (built_env(env, data.argv, data.out));
	else if (!ft_strcmp(data.argv[0], "exit"))
		built_exit(data.argv, env); // attention exit ne ferme pas forcement minishell
	return (-1);
}

int	execution(char *line_read, t_data *data)
{
	int		i;
	int		pipefd[2];
	int 	tmp_fd;
	int		nb_cmd;
	pid_t	*f_pid;
	int		j;
	
	i = 0;
	tmp_fd = 3;
	analyse(line_read, &i, data);
	nb_cmd = data->nb_cmd;
	f_pid = malloc(sizeof(int) * nb_cmd); // sécuriser malloc !
	j = 0;
	while (j < nb_cmd - 1)
	{
		if (pipe(pipefd) == -1)
			error("pipe"); // return si le pipe ne fonctionne pas ?
		if (data->argv)
		{
			f_pid[j] = fork_loop(data, pipefd, env, &tmp_fd);
			ft_free(data->argv);
		}
		analyse(line_read, &i, &data);
		j++;
	}
	if (data.argv)
	{
		if (builtins(data, env) == -1)
			f_pid[j] = fork_loop(&data, pipefd, env, &tmp_fd);
		close(tmp_fd);
		ft_free(data.argv);
	}
	j = 0;
	while (j < nb_cmd)
	{
		waitpid(f_pid[j], &data.last_return, 0);
		j++;
	}
	free(f_pid);
	return (data.last_return);
}
