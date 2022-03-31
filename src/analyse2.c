/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:58:06 by njaros            #+#    #+#             */
/*   Updated: 2022/03/31 13:52:56 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*organiser(t_list **pouet, int i, char *str, t_data *data)
{
	t_list	*first;
	int		lg;

	lg = chevronnage(pouet, data);
	first = *pouet;
	
}