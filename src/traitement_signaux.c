#include "coquillette.h"

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	ft_putstr_fd("\ncoquillette0.1>", 1);
	rl_redisplay();
}

void	init_sigact(struct sigaction *act)
{
	act->sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act->sa_sigaction = handler;
	sigaction(SIGINT, act, NULL);
	sigaction(SIGQUIT, act, NULL);
}