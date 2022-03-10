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

#include "../includes/coquillette.h"

char    *get_cmd(char *cmd, char **path)
{
    char    *cmd_path;
    char    *tmp;
    int     i;

    cmd_path = NULL;
    i = 0;
    while(path[i])
    {
        printf("blop\n");
        tmp = ft_strjoin(path[i], "/");
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(cmd_path, X_OK) == 0)
            break ;
        free(cmd_path);
        i++;
    }
    printf("%s\n", cmd_path);
    return (cmd_path);
}

int main(int argc, char *argv[], char **envp)
{
    int     pipefd[2];
    pid_t   pid1;
    pid_t   pid2;
    int     fd1;
    int     fd2;
    char    *cmd1;
    char    **cmd1_arg;
    char    *cmd2;
    char    **cmd2_arg;
    char    *env;
    char    **path;

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[4], O_WRONLY);
    if (fd1 < 0 || fd2 < 0)
        exit(EXIT_FAILURE);
    env = getenv("PATH");
    path = ft_split(&env[5], ':');
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {  // if fork() returns 0, we are in the child process */ //exécution de la commande 1
        dup2(fd1, STDIN_FILENO); // we want fd1 to be execve(cmd1) input
        dup2(pipefd[1], STDOUT_FILENO); // on envoie dans le tuyau le résultat de la cmd1 sur fd1
        close(pipefd[0]);        /* Close unused pipe end */ // as long as the pipe is open, the other end will be waiting for some kind of input and will not be able to finish its process
        cmd1_arg = ft_split(argv[2], ' ');
        cmd1 = get_cmd(cmd1_arg[0], path);
        printf("%s\n", cmd1);
        if (cmd1 == NULL)
            exit(EXIT_FAILURE);
        if (execve(cmd1, cmd1_arg, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        close(fd1);
        free(cmd1_arg);
        free(cmd1);
    }
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork2");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {  // if fork() returns 0, we are in the child process */ //exécution de la commande 1
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        dup2(fd2, 1);
        cmd2_arg = ft_split(argv[3], ' ');
        cmd2 = get_cmd(cmd2_arg[0], path);
        if (cmd2 == NULL)
            exit(EXIT_FAILURE);
        printf("%s\n", cmd2);
        if (execve(cmd2, cmd2_arg, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        close(fd2);
        close(pipefd[0]);
        free(cmd2_arg);
        free(cmd2);
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    free(path);
    return (0);
}
