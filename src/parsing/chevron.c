/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:07 by njaros            #+#    #+#             */
/*   Updated: 2022/04/25 15:38:05 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	file_to_open(char *file, int chev, t_data *data)
{
	int		fd;

	if (chev == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (chev == 2)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (chev == 3)
		fd = open(file, O_RDONLY);
	else
		fd = ft_atoi(file);
	if (chev == 1 || chev == 2)
		data->out = fd;
	if (chev == 3 || chev == 4)
		data->in = fd;
	if (fd == -1)
	{
		ft_putstr_fd("coquillette: ", 2);
		data->last_return = 1;
		perror(file);
	}
}

int	manip_chevron_str(char **str)
{
	int	i;

	i = 0;
	while (str[0][i] == '>')
		i++;
	if (i > 0)
	{
		*str += i;
		while (*str[0] == ' ')
			*str += 1;
		return (i);
	}
	while (str[0][i] == '<')
		i++;
	if (i > 0)
	{
		*str += i;
		while (*str[0] == ' ')
			*str += 1;
		return (2 + i);
	}
	return (0);
}

int	chevron_manager(t_list **pouet, t_list *prev, t_data *data)
{
	char	*content;
	int		chevron_type;

	content = (*pouet)->content;
	chevron_type = manip_chevron_str(&content);
	if (!chevron_type)
		return (0);
	if (chevron_type != 4)
		content = quote_doll_handler(content, data);
	if (!content)
		error("coquillette : chevron_manager :");
	file_to_open(content, chevron_type, data);
	if (chevron_type != 4)
		free(content);
	reorder_lst(pouet, prev);
	return (1);
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
			if (first == NULL)
				first = *pouet;
			lg++;
			prev = *pouet;
			*pouet = (*pouet)->next;
		}
	}
	*pouet = first;
	return (lg);
}
