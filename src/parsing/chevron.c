/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:07 by njaros            #+#    #+#             */
/*   Updated: 2022/04/08 14:04:20 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	ft_heredoc(char *end)
{
	char	*line_read;
	int 	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	line_read = readline(">");
	while (line_read && strcmp(line_read, end))
	{
		ft_putendl_fd(line_read, fd[1]);
		free(line_read);
		line_read = readline(">");
	}
	free(line_read);
	close(fd[1]);
	return (fd[0]);
}

void	file_to_open(char *file, int chev, t_data *data)
{
	int	fd;

	if (chev == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 644);
	else if (chev == 2)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 644);
	else if (chev == 3)
		fd = open(file, O_RDONLY);
	else if (chev == 4)
		fd = ft_heredoc(file);
	if (chev == 1 || chev == 2)
		data->out = fd;
	if (chev == 3 || chev == 4)
		data->in = fd;
	if (fd == -1)
		analyse_error_message(file, errno);
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
	char	*next_cont;
	int		i;
	int		chevron_type;

	content = (*pouet)->content;
	chevron_type = manip_chevron_str(&content);
	if (!chevron_type)
		return (0);
	if (chevron_type != 4)
		content = quote_doll_handler(content, data);
	else
		content = only_quote_handler(content);
	if (!content)
		return (analyse_error_message("chevron_manager", ENOMEM));
	file_to_open(content, chevron_type, data);
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
		if (!chevron_manager(pouet, prev, data))
		{
			if (first == NULL)
				first = *pouet;
			lg++;
			prev = *pouet;
			*pouet = (*pouet)->next;
		}
	*pouet = first;
	return (lg);
}
