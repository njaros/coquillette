/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:53:32 by marvin            #+#    #+#             */
/*   Updated: 2022/03/14 11:26:53 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void    error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void    feel_free(t_pipe *pip)
{
    free(pip->cmd1);
    free(pip->cmd2);
    ft_free(pip->cmd1_arg);
    ft_free(pip->cmd2_arg);
    ft_free(pip->path);
}
