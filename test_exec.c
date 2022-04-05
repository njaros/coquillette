#include "includes/coquillette.h"

void	error_message(char *str, int context)
{
	write(2, "coquillette: ", 14);
	write(2, str, ft_strlen(str));
	write(2, ": ", 3);
	ft_putendl_fd(strerror(context), 2);
}

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
	int		cmd_ret;

	env = getenv("PATH");
	path = ft_split(env, ':');
	cmd_arg = ft_split(argv[1], ' ');
	cmd_path = get_cmd(cmd_arg[0], path);
	// if (access(cmd_path, X_OK) == -1)
	// 	error_message(cmd_arg[0], errno);
	// if (!cmd_path)
	// 	return (-1);
	pid = fork();
    if (pid == 0)
	{
		printf("depart fork\n");
		execve(cmd_path, cmd_arg, envp) == -1)
			return (-1); // printer message d'erreur et exit !
		// attention penser à mettre à jour la valeur cmd_ret
	}
   	wait(&cmd_ret);
	//error_message(cmd_arg[0], errno);
	return (0);
}