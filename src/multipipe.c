/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:22:59 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/30 16:10:19 by ccartet          ###   ########.fr       */
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

void	test_multipipe()
{
	int		pip_nb;
	t_pipe	pip;
	int		fd[2];
	int		tmp_fd;
	pid_t	fork_pid;

	pip_nb = 2; // recuperer le nb de pipe => parsing
	while (pip_nb > 0)
	{
		if (pipe(fd) == -1)
      		error("pipe");
		fork_pid = fork(); // ou builtins
			error("fork");
		if (fork_pid == 0)
		{
			if (dup2(pip->infile, STDIN_FILENO) == -1)
       			error("dup");
    		close(fd[0]);
    		if (dup2(fd[1], STDOUT_FILENO) == -1)
        		error("dup");
    		close(pip->infile);
    		if (execve(pip->cmd1, pip->cmd1_arg, envp) == -1)
        		error("execve");
		}
		pip_nb--;
	}
}

void	test_exec(char *line_read, t_list *env, char **path)
{
	int		i;
	t_tpipe	data;
	int		pipefd[2];
	pid_t	f_pid;
	
	i = 0;
	while (analyse(line_read, &i, &data)) // read_line a déjà été tranformée
	{
		if (data.pipe)
			if (pipe(pipefd) == -1)
				error("pipe");
		if (check_built(data.cmd_arg[0])) // vérifier si la cmd est un builtin
			builtins(data.cmd_arg, env, data.out);
		else
		{
			if (!data.cmd_path) // vérifier que la commande existe
				printf("%s: command not found\n", data.cmd_arg[0]);
			else
			{
				f_pid = fork();
				if (f_pid == -1)
					perror("fork");
				if (f_pid == 0)
				{
					fd = pipefd[0]; // puis fd = retour de cette petite fonction
					if (data.in == -1) // pas 0 ou autre fd d'entrée
						data.in = fd; // fd[0] récupéré de la sortie de precedent passage de boucle
					dup2(data.in, STDIN_FILENO);
    				//close(pipefd[0]); // comment ça se passe ?!!!
					if (data.out == -1) // pas 1 ou autre fd de sortie
						data.out = pipefd[1];
    				dup2(data.out, STDOUT_FILENO);
    				//close(data.in);
					execve(data.cmd_path, data.cmd_arg, env);
			
				}
				close(pipefd[1]);
				close(pipefd[0]);
				waitpid(f_pid, NULL, 0);
				return (fd);
			}
		}
		

	}
}



