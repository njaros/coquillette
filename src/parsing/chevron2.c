/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:24:45 by njaros            #+#    #+#             */
/*   Updated: 2022/04/19 14:01:18 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	heredoc_fork(int fd, char *end)
{
	char	*line_read;

	line_read = readline("> ");
	while (line_read && strcmp(line_read, end))
	{
		ft_putendl_fd(line_read, fd);
		free(line_read);
		line_read = readline(">");
	}
	ft_putchar_fd('\0', fd);
	free(line_read);
	close(fd);
	exit(0);
}