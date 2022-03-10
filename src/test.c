#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int	get_fd_rdonly(char *entry)
{
	int	i;
	int	fd;

	i = -1;
	while (entry[++i])
	{
		if (entry[i] < '0' && entry[i] > '9')
			return (open(entry, O_RDONLY));
	}
	fd = open(entry, O_RDONLY);
	if (fd < 0)
		return (atoi(entry));
	else
		return (fd);
}

int main(int ac, char **av)
{
	int	fd;

	fd = get_fd_rdonly(av[1]);
	printf("le fd est : %d\n", fd);
	if (isatty(fd))
		printf("nom du tty : %s\n", ttyname(fd));
	printf("ttyslot affiche %d\n", ttyslot());
	return (0);
}
