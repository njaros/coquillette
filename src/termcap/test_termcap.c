#include <stdlib.h>
#include <stdio.h>
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <errno.h>

void	error(char *msg)
{
	perror("msg");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char	*term_type;
	int		ret;
	char	*cl_cap;
	// struct termios s_termios;
 	// struct termios s_termios_backup;
	(void)argc;
	(void)argv;

	term_type = getenv("TERM");
	if (term_type == NULL)
		error("TERM must be set (see 'env').\n");
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		error("Could not access to the termcap database..\n");
	if (ret == 0)
		error("Terminal type `%s' is not defined.\n");
	// if (tcgetattr(0, &s_termios) == -1)
    //       return (-1);
    // if (tcgetattr(0, &s_termios_backup) == -1)
    //       return (-1);
	printf("%d\n", tgetnum("co"));
	printf("%d\n", tgetnum("li"));
	// if (tgetflag("os") != 0)
	// {

	// }
	cl_cap = tgetstr("cl", NULL); // pour récupérer le termcap de clear, attentien à free notre char *
	tputs (cl_cap, 1, putchar);
//	pour modifier la couleur du texte par exemple
	char *color_cap = tgetstr("AF", NULL);
	tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);
	printf("Cool ! Maintenant j'ecris en vert !\n");
//	pour réinitialiser les attributs du terminal
	char *reset_cmd = tgetstr("me", NULL);
	tputs(reset_cmd, 1, putchar);
//	pour déplacer notre curseur
	char *cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, 5, 5), 1, putchar);
	return (errno);
}
