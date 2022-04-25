/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:41:51 by njaros            #+#    #+#             */
/*   Updated: 2022/04/25 13:43:33 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*signaled_heredoc(int fd_in, int fd_out)
{
	write(1, "\n", 1);
	close(fd_out);
	close(fd_in);
	kill(0, SIGUSR2);
	return (NULL);
}
