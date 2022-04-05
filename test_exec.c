#include "includes/coquillette.h"

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

int	main(int argc, char **argv, char **envp)
{
	pid_t   pid;
	char    *env;
	char	**path;
	char	**cmd_arg;
	char	*cmd_path;

	env = getenv("PATH");
	path = ft_split(env, ':');
	cmd_arg = ft_split(argv[1], ' ');
	cmd_path = get_cmd(cmd_arg[0], path);
	pid = fork();
    if (pid == 0)
	{
		printf("depart fork\n");
		//execve(cmd_path, cmd_arg, envp);
	}
    waitpid(pid, NULL, 0);
	printf("blop\n");
	return (0);
}