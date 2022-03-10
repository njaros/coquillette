#include "coquillette.h"

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		rl_redisplay();
		//ft_putstr_fd("\ncoquillette0.1>", 1);
		//ft_putstr_fd(rl_line_buffer, 1);
		return ;
	}
	(void) ucontext;
	ft_putendl_fd("\nquit", 1);
	exit(EXIT_SUCCESS);
}

void	init_sigact(struct sigaction *act)
{
	act->sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act->sa_sigaction = handler;
	sigaction(SIGINT, act, NULL);
	sigaction(SIGQUIT, act, NULL);
}