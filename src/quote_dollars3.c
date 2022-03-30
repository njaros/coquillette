/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollars3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:48:05 by njaros            #+#    #+#             */
/*   Updated: 2022/03/30 10:18:32 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	le_coupable_est(char *c)
{
	write(2, "syntax error near unexpected token `", 37);
	if (!*c || *c == '\n')
		write(2, "newline'\n", 10);
	else
	{
		write(2, c, 1);
		write(2, "'\n", 3);
	}
}
