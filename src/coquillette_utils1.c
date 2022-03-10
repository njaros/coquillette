/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coquillette_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:20:42 by njaros            #+#    #+#             */
/*   Updated: 2022/03/08 16:46:37 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*rl_get(char *line_read)
{
	if (line_read)
		free(line_read);
	line_read = readline("coquillette0.1>");
	if (!line_read)
	{
		ft_putchar_fd('\n', 1);
		exit(EXIT_SUCCESS);
	}
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
