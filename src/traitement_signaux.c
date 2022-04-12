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

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static int	prompt = 1;

	if (sig == SIGUSR1 && siginfo->si_pid == getpid())
	{
		prompt = ft_switch(prompt);
		return ;
	}
	if (sig == SIGQUIT)
		return ;
	if (prompt)
		ft_putstr_fd("\n\e[34mcoquillette0.1>\e[0m", 1);
	rl_replace_line("", 0);
}

void	init_sigact(struct sigaction *act)
{
	act->sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act->sa_sigaction = handler;
	sigaction(SIGINT, act, NULL);
	sigaction(SIGQUIT, act, NULL);
	sigaction(SIGUSR1, act, NULL);
}
