/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traitement_signaux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:49:37 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/07 10:49:37 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	terminal_handler(int end)
{
	int						fd_term;
	struct termios			term_minishell;
	static struct termios	term_before;

	fd_term = ttyslot();
	if (end)
	{
		tcsetattr(fd_term, TCSANOW, &term_before);
		return ;
	}
	tcgetattr(fd_term, &term_before);
	term_minishell = term_before;
	term_minishell.c_cc[VQUIT] = 0;
	term_minishell.c_lflag &= ~ECHOCTL;
	tcsetattr(fd_term, TCSANOW, &term_minishell);
}

void	reset_readline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	write(0, "\n", 1);
	rl_redisplay();
	*g_return_ptr = 1;
}

void	signal_handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static int	pid_father = 0;
	static int	pid_fork = -1;

	(void)ucontext;
	if (sig == SIGUSR2)
	{
		pid_father = siginfo->si_pid;
		pid_fork = -1;
	}
	else if (sig == SIGUSR1)
	{
		if (pid_fork == -1)
			pid_fork = siginfo->si_pid;
		else
			pid_fork = -1;
	}
	else if (sig == SIGINT && siginfo->si_pid == pid_father)
	{
		reset_readline();
		return ;
	}
	else if (sig == SIGINT && siginfo->si_pid == pid_fork)
		exit(siginfo->si_signo);
	else if (sig == SIGINT && pid_fork == -1)
		write(1, "^C\n", 3);
}

void	init(struct sigaction *act, t_data *data, t_list *env_list)
{
	data->env = env_list;
	data->argv = NULL;
	data->last_return = 0;
	g_return_ptr = &data->last_return;
	terminal_handler(0);
	act->sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act->sa_sigaction = signal_handler;
	sigaction(SIGINT, act, NULL);
	sigaction(SIGUSR2, act, NULL);
	sigaction(SIGUSR1, act, NULL);
}
