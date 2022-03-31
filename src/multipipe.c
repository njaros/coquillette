/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:22:59 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/31 16:43:26 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

typedef struct s_tpipe
{
    int     infile;
    int     outfile;
    char    **cmd_arg;
	char	*cmd_path;
	int		pipe;
}               t_tpipe;

int	loop_pipe(t_tpipe *data, int *fd_in, int pipefd[2])
{
	pid_t	f_pid;
	
	f_pid = fork();
	if (f_pid == -1)
		perror("fork");
	if (f_pid == 0)
	{
		if (data->in == -1) // pas 1e cmd donc je lui passe le fd_in récupéré du précédemment passage
			data->in = fd_in;
		dup2(data->in, STDIN_FILENO);
		close(pipefd[0]);
		if (data->out == -1) // sauf derniere cmd
			data->out = pipefd[1];
		dup2(data->out, STDOUT_FILENO);
		execve(data->cmd_path, data->cmd_arg, env);
	}
	close(data->out);
	close(data->in);
	waitpid(f_pid, NULL, 0);
	return (pipefd[0]);
}

void	test_exec(char *line_read, t_list *env, char **path)
{
	int		i;
	t_tpipe	data;
	int		pipefd[2];
	pid_t	f_pid;
	int		tmp_fd;
	
	i = 0;
	tmp_fd = 0;
	while (analyse(line_read, &i, &data) == 1) // read_line a déjà été transformée
	{
		if (pipe(pipefd) == -1)
			error("pipe");
		if (check_built(data.cmd_arg[0])) // vérifier si la cmd est un builtin
			builtins(data.cmd_arg, env, data.out);
		else
		{
			data.cmd_path = found_cmd(data.cmd_arg[0]);
			if (!data.cmd_path) // vérifier que la commande existe
				printf("%s: command not found\n", data.cmd_arg[0]);
			else
				tmp_fd = loop_pipe(&data, tmp_fd, pipefd);
		}
	}
	// dernier passage, on sort de la boucle car plus besoin de créer de nouveau pipe !
	if (check_built(data.cmd_arg[0])) // vérifier si la cmd est un builtin
		builtins(data.cmd_arg, env, data.out);
	else
	{
		data.cmd_path = found_cmd(data.cmd_arg[0]);
		if (!data.cmd_path) // vérifier que la commande existe
			printf("%s: command not found\n", data.cmd_arg[0]);
		else
		loop_pipe(&data, tmp_fd, pipefd);
	}
}
