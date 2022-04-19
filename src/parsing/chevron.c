/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:07 by njaros            #+#    #+#             */
/*   Updated: 2022/04/19 13:56:43 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	ft_heredoc(char *end)
{
	int 	fd[2];
	int		ret;
	int		pid_fork;

	if (pipe(fd) == -1)
		error("coquillette: analyse: ft_heredoc: pipe");
	pid_fork = fork();
	if (pid_fork == -1)
		error("coquillette: analyse: ft_heredoc: fork");
	if (pid_fork == 0)
		heredoc_fork(fd[1], end);
	waitpid(pid_fork, &ret, 0);
	//if ()
	return (fd[0]);
}

void	file_to_open(char *file, int chev, t_data *data)
{
	int	fd;

	if (chev == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (chev == 2)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (chev == 3)
		fd = open(file, O_RDONLY);
	else if (chev == 4)
		fd = ft_heredoc(file);
	if (chev == 1 || chev == 2)
		data->out = fd;
	if (chev == 3 || chev == 4)
		data->in = fd;
	if (fd == -1)
	{
		ft_putstr_fd("coquillette: ", 2);
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
		error("coquillette : chevron_manager :");
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
