/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:41:30 by njaros            #+#    #+#             */
/*   Updated: 2021/11/20 10:41:30 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contain_return(char *s)
{
	int	i;

	i = -1;
	if (s)
	{
		while (s[++i])
		{
			if (s[i] == '\n')
				return (i);
		}
	}
	return (i);
}

char	*ft_return_and_keep(char **temp, char *line, int n)
{
	char	*str;

	str = ft_substr(line, 0, n + 1);
	*temp = ft_substr_free(line, n + 1, ft_strlen(&line[n + 1]));
	return (str);
}

char	*get_next_line(int fd)
{
	int			i;
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	static char	*temp;

	line = NULL;
	i = (contain_return(temp));
	if (temp && temp[i] == '\n')
		return (ft_return_and_keep(&temp, temp, i));
	line = ft_strjoin_free(line, temp, 2);
	i = 0;
	ft_bzero(buf, BUFFER_SIZE + 1);
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_free(line, buf, 1);
		i = i + (contain_return(&line[i]));
		if (line[i] == '\n')
			return (ft_return_and_keep(&temp, line, i));
		ft_bzero(buf, BUFFER_SIZE + 1);
	}
	temp = NULL;
	return (line);
}
