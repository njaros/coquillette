/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:24:45 by njaros            #+#    #+#             */
/*   Updated: 2022/04/22 16:31:08 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	heredoc_fork(int fd, char *eof)
{
	char	*line_read;
	char	*noqeof;

	noqeof = only_quote_handler(eof);
	if (!eof)
		error("coquillette: heredoc: only_quote_handler: malloc");
	kill (0, SIGUSR1);
	line_read = readline(">");
	while (line_read && strcmp(line_read, noqeof))
	{
		ft_putendl_fd(line_read, fd);
		free(line_read);
		line_read = readline(">");
	}
	kill (0, SIGUSR1);
	free(line_read);
	free(noqeof);
	exit(0);
}

char	*ft_heredoc(char *eof)
{
	int		fd[2];
	int		ret;
	int		pid_fork;
	char	*itoa_fd;

	if (pipe(fd) == -1)
		error("coquillette: parsing: ft_heredoc: pipe");
	itoa_fd = ft_itoa(fd[0]);
	if (!itoa_fd)
		error("coquillette: parsing: ft_heredoc: malloc");
	pid_fork = fork();
	if (pid_fork == -1)
		error("coquillette: parsing: ft_heredoc: fork");
	if (pid_fork == 0)
		heredoc_fork(fd[1], eof);
	waitpid(pid_fork, &ret, 0);
	if (ret)
	{
		close(fd[0]);
		close(fd[1]);
		kill(0, SIGUSR2);
		return (NULL);
	}
	close(fd[1]);
	return (itoa_fd);
}

int	is_heredoc(char *str, int quote, int dquote)
{
	if (quote | dquote)
		return (0);
	if (str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}

char	*parse_heredoc(char *str, int *i)
{
	char	*new;
	char	*eof;
	int		j;

	j = *i;
	while (!ft_tokenchar(str[*i]) && str[*i] != ' ')
		*i += 1;
	eof = ft_substr(str, j, *i - j);
	if (!eof)
		error("coquillette: parsing: heredoc: malloc");
	eof = ft_heredoc(eof);
	if (!eof)
		return (NULL);
	new = ft_calloc(ft_strlen(str) - (*i - j) + ft_strlen(eof) + 1, 1);
	if (!new)
		error("coquillette: parsing: heredoc: ft_calloc");
	ft_strlcpy(new, str, j + 1);
	ft_strcat(new, eof);
	ft_strcat(new, &str[*i]);
	*i = j + ft_strlen(eof);
	free(eof);
	free(str);
	return (new);
}

char	*heredoc_handler(char *str)
{
	int		quote;
	int		dquote;
	int		i;

	quote = 0;
	dquote = 0;
	i = -1;
	while (str[++i])
	{
		quote_switcher(&quote, &dquote, str[i]);
		if (is_heredoc(&str[i], quote, dquote))
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			str = parse_heredoc(str, &i);
			if (!str)
				return (NULL);
		}
	}
	return (str);
}
