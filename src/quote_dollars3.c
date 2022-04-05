/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:48:05 by njaros            #+#    #+#             */
/*   Updated: 2022/04/05 15:41:44 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	le_coupable_est(char *c)
{
	write(2, "coquillette: syntax error near unexpected token `", 50);
	if (!*c || *c == '\n')
		write(2, "newline'\n", 10);
	else
	{
		write(2, c, 1);
		write(2, "'\n", 3);
	}
}

int	alone_pipe(char *str, int *i)
{
	while (str[++(*i)] == ' ')
		;
	if (str[*i] == '|')
		return (1);
	return (0);
}

int	last_char_is_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (1);
	return (0); 
}