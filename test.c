#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[], char **envp)
{
	int	fd;
	char	*env;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		printf("Damn: %s\n", strerror(errno));
	if (fd == -1)
        perror("Error");
	// dup2(fd, STDIN_FILENO);
	return (0);
}