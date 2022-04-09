#include <unistd.h>

int	main(void)
{
	int	int_mode;

	int_mode = 1;
	while(int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
			write(STDOUT_FILENO, "~$ ", 13);
	}
	return (0);
}

Protect the standard input file descriptor:
if (!isatty(STDIN_FILENO))
isatty is a function that checks if the standard input is pointing to our terminal
(which is usually the case for 0, 1 and 2 file descriptors). This is important because
we will use the STDIN fd in many termcaps functions. If it is not valid it is important
to identify this error as soon as possible to display the correct error message
(using the appropriate errno).

Save terminal settings before we change them using tcgetattr. The settings are saved
in a struct termios
struct termios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[NCCS];
	speed_t c_ispeed;
	speed_t c_ospeed;
};

Using the tgetent function we check if there is a terminfo database
(database with all terminal capabilities) for the TERM environment variable
in our envp array and load the functions internally, so that the tgetstr
function works.