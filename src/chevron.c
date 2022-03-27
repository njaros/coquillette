//#include "coquillette.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	fichier_a_ouvrir(char *file, char *chev)
{
	int	fd;

	if (ft_strcmp(chev, ">") == 0)
		fd = open(file, O_WRONLY | O_TRUNC);
	else if (ft_strcmp(chev, ">>") == 0)
		fd = open(file, O_WRONLY | O_APPEND);
	else if (ft_strcmp(chev, "<") == 0)
		fd = open(file, O_RDONLY);
	else if (ft_strcmp(chev, "<<") == 0)
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	int		fd;
	char	*cmd;
	
	fd = fichier_a_vider(av[1]);
	if (fd == -1)
	{
		write(1, "CKC\n", 5);
	}
	close(fd);
	return (0);
}
