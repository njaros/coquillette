#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void	signal_handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static int	pid_father;

	if (sig == SIGQUIT)
	{
		printf("SIGQUIT recu, arret obligatoire pour tout le monde\n");
		exit(siginfo->si_signo);
	}
	if (sig == SIGUSR2)
	{
		printf("handler prend connaissance du pid du pere %d\n", siginfo->si_pid);
		pid_father = siginfo->si_pid;
		return ;
	}
	else if (getpid() == pid_father)
		return ;
	printf("\n--le processus enfant a recu le signal %d et doit exit --\n", siginfo->si_signo);
	printf("fin du processus enfant %d\n", getpid());
	//exit(siginfo->si_signo);
}

int	main(void)
{
	int					pid;
	int					ret;
	int					in_fork_sleep_val;
	struct sigaction	act;

	printf("processus parent : %d\n", getpid());
	act.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act.sa_sigaction = signal_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	kill(getpid(), SIGUSR2);
	while (1)
	{
		printf("\n\n     ----RAPPEL----\n   Pour stopper un processus enfant : CTRL C\n   Pour stopper le programme : CTRL \\ (ou SIGKILL au pire)\n\n");
		pid = fork();
		if (pid == 0)
		{
			printf("debut de processus enfant : %d\n", getpid());
			in_fork_sleep_val = sleep(5);
			if (!in_fork_sleep_val)
				printf("pas de signal d'arret recu pour ce processus enfant\n fin du processus enfant %d\n", getpid());
			exit(in_fork_sleep_val);
		}
		waitpid(pid, &ret, 0);
		printf("ret = %d\nWIFEXITED = %d\nWEXITSTATUS = %d\n", ret, WIFEXITED(ret), WEXITSTATUS(ret));
		if (WIFSIGNALED(ret))
			printf("WTERMSIG = %d\n", WTERMSIG(ret));
		if (WIFSTOPPED(ret))
			printf("WSTOPSIG = %d\n", WSTOPSIG(ret));
	}
	return (0);
}