#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	get_fd_rdonly(char *entry)
{
	int	i;

	i = 0;
	while (entry[i])
	{
		if (entry[i] <= '9' && entry[i] >= '0')
			i++;
		else
			break ;
	}
	if (entry[i] == 0)
		return (atoi(entry));
	else
		return (open(entry, O_RDONLY));
}

int main(int ac, char **av)
{
	int	fd;

	fd = get_fd_rdonly(av[1]);
	if (isatty(fd))
		printf("nom du tty : %s\n", ttyname(fd));
	printf("ttyslot affiche %d\n", ttyslot());
	return (0);
}
