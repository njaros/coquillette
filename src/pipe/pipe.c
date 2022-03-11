/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:09:26 by marvin            #+#    #+#             */
/*   Updated: 2022/03/10 16:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coquillette.h"

char    *get_cmd(char *cmd, char **path)
{
    char    *cmd_path;
    char    *tmp;
    int     i;

    cmd_path = NULL;
    i = 0;
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(cmd_path, X_OK) == 0)
            break ;
        free(cmd_path);
        cmd_path = NULL;
        i++;
    }
    return (cmd_path);
}

void    child_two(t_pipe *pip, int *fd, char **envp)
{
    if (dup2(fd[0], STDIN_FILENO) == -1)
        error("dup");
    close(fd[1]);
    if (dup2(pip->outfile, STDOUT_FILENO) == -1)
        error("dup");
    close(pip->outfile);
    if (execve(pip->cmd2, pip->cmd2_arg, envp) == -1)
        error("execve");
}

void    child_one(t_pipe *pip, int *fd, char **envp)
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

void    init(t_pipe *pip, char **argv)
{
    char    *env;

    pip->infile = open(argv[1], O_RDONLY);
    pip->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pip->infile < 0 || pip->outfile < 0)
        error("fd");
    env = getenv("PATH");
    pip->path = ft_split(env, ':');
    pip->cmd1_arg = ft_split(argv[2], ' ');
    pip->cmd1 = get_cmd(pip->cmd1_arg[0], pip->path);
    if (pip->cmd1 == NULL)
        error("access"); // à tester !!
    pip->cmd2_arg = ft_split(argv[3], ' ');
    pip->cmd2 = get_cmd(pip->cmd2_arg[0], pip->path);
    if (pip->cmd2 == NULL)
        error("access"); // à tester !!
}

int main(int argc, char *argv[], char **envp)
{
    t_pipe  pip;
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;

    init(&pip, argv);
    if (pipe(fd) == -1)
        error("pipe");
    pid1 = fork();
    if (pid1 == -1)
        error("fork1");
    if (pid1 == 0)
        child_one(&pip, fd, envp);
    pid2 = fork();
    if (pid2 == -1)
        error("fork2");
    if (pid2 == 0)
        child_two(&pip, fd, envp);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    feel_free(&pip);
    return (errno);
}
