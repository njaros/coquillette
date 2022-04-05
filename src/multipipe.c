/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:22:59 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/05 12:15:59 by ccartet          ###   ########.fr       */
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
	cmd = get_cmd(entry, path_tab);
	ft_free(path_tab);
	//free(entry);
	return (cmd);
}

char **transform_list(t_list *env)
{
	char	**envp;
	int		size;
	int		i;
	t_env	*tmp;
	char	*first;
	
	size = ft_lstsize(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = env->content;
		first = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(first, tmp->value);
		free(first);
		i++;
		env = env->next;
	}
	return (envp);
}

int	loop_pipe(t_data *data, int fd_in, int pipefd[2], t_list *env)
{
	pid_t	f_pid;
	char	**envp;
	
	f_pid = fork();
	if (f_pid == -1)
		perror("fork");
	if (f_pid == 0)
	{
		if (data->in == -2) // pas 1e cmd donc je lui passe le fd_in récupéré du précédemment passage
			data->in = fd_in;
		dup2(data->in, STDIN_FILENO);
		close(pipefd[0]);
		if (data->out == -2) // sauf derniere cmd
			data->out = pipefd[1];
		dup2(data->out, STDOUT_FILENO);
		envp = transform_list(env);
		execve(data->cmd_path, data->argv, envp);
		ft_free(envp);
	}
	close(data->out);
	close(data->in);
	waitpid(f_pid, NULL, 0);
	return (pipefd[0]);
}

void	lecture(char **str)
{
	int i;
	i = -1;
	while (str[++i])
		write(2, str[i], ft_strlen(str[i]));
}

void	test_exec(char *line_read, t_list *env)
{
	int		i;
	t_data	data;
	int		pipefd[2];
	pid_t	f_pid;
	int		tmp_fd;
	
	i = 0;
	tmp_fd = 0;
	while (analyse(line_read, &i, &data) == 1) // read_line a déjà été transformée
	{
		if (pipe(pipefd) == -1)
			error("pipe");
		// if (check_built(data.cmd_arg[0])) // vérifier si la cmd est un builtin
		// 	builtins(data.cmd_arg, env, data.out);
		else if (data.argv)
		{
			data.cmd_path = found_cmd(data.argv[0]);
			if (!data.cmd_path) // vérifier que la commande existe
				printf("%s: command not found\n", data.argv[0]);
			else
				tmp_fd = loop_pipe(&data, tmp_fd, pipefd, env);
		}
		if (data.argv)
		{
			ft_free(data.argv);
			free(data.cmd_path);
		}
	}
	// dernier passage, on sort de la boucle car plus besoin de créer de nouveau pipe !
	// if (check_built(data.argv[0])) // vérifier si la cmd est un builtin
	// 	builtins(data.argv, env, data.out);
	// else
	//// {
		if (data.argv)
		{
			data.cmd_path = found_cmd(data.argv[0]);
			if (!data.cmd_path) // vérifier que la commande existe
				printf("%s: command not found\n", data.argv[0]);
			else
				loop_pipe(&data, tmp_fd, pipefd, env);
			ft_free(data.argv);
			free(data.cmd_path);
		}
	// }
}

if (data.argv) // passer dans l'execution 