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
	if (sig == SIGQUIT)
	{
		//rl_redisplay();
		return ;
	}
	ft_putstr_fd("\n", 1);
}

void	init_sigact(struct sigaction *act)
{
	act->sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act->sa_sigaction = handler;
	sigaction(SIGINT, act, NULL);
	sigaction(SIGQUIT, act, NULL);
}
