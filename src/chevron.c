/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:07 by njaros            #+#    #+#             */
/*   Updated: 2022/03/31 15:56:33 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	file_to_open(char *file, int chev, t_data *data)
{
	int	fd;

	if (chev == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT);
	else if (chev == 2) 
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT);
	else if (chev == 3)
		fd = open(file, O_RDONLY);
	else if (chev == 4)
		fd = -1;
		//heredoc à faire ICI
	if (chev == 1 || chev == 2)
		data->out = fd;
	if (chev == 3 || chev == 4)
		data->in = fd;
	if (fd == -1)
		analyse_error_message(file, 1);
}

int	manip_chevron_str(char **str)
{
	int	i;

	i = 0;
	while (*str[i] == '>')
		i++;
	if (i > 0)
	{
		*str += i;
		return (i);
	}
	while (*str[i] == '<')
		i++;
	if (i < 0)
	{
		*str += i;
		return (2 + i);
	}
	return (0);
}

int	chevron_manager(t_list **pouet, t_list *prev, t_data *data)
{
	char	*content;
	char	*next_cont;
	int		i;
	int		chevron_type;

	content = (*pouet)->content;
	chevron_type = manip_chevron_str(&content);
	if (chevron_type)
	{
		if (!content[0])
		{
			next_cont = (*pouet)->next->content;
			file_to_open(next_cont, chevron_type, data);
			reorder_lst(pouet, prev, 2);
		}
		else
		{
			file_to_open(content, chevron_type, data);
			reorder_lst(pouet, prev, 1);
		}
		return (1);
	}
	return (0);
}

int	chevronnage(t_list **pouet, t_data *data)
{
	t_list	*first;
	t_list	*prev;
	int		lg;

	lg = 0;
	first = NULL;
	prev = NULL;
	while (*pouet)
	{
		if (!chevron_manager(pouet, prev, data))
		{
			if (first = NULL)
				first = *pouet;
			lg++;
			prev = *pouet;
		}
		*pouet = (*pouet)->next;
	}
	return (lg);
}
