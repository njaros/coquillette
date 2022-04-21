/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:58:06 by njaros            #+#    #+#             */
/*   Updated: 2022/04/21 14:45:32 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	lst_dequotage(t_list *lst, t_data *data)
{
	char	*formated;

	while (lst)
	{
		formated = quote_doll_handler((char *)lst->content, data);
		free(lst->content);
		if (!formated)
			return (0);
		lst->content = formated;
		lst = lst->next;
	}
	return (1);
}

int	end_parsing(char *str, int *i, t_data *data)
{
	if (str[*i] == '|')
	{
		*i += 1;
		return (1);
	}
	if (data->out == -2)
		data->out = 1;
	return (0);
}

int	organiser(t_list **pouet, int *i, char *str, t_data *data)
{
	t_list	*first;
	int		lg;
	int		j;

	j = -1;
	lg = chevronnage(pouet, data);
	if (!lst_dequotage(*pouet, data))
		error("analyse: organiser: lst_dequotage");
	first = *pouet;
	if (!lg)
		return (end_parsing(str, i, data));
	data->argv = malloc(sizeof(char *) * lg + 1);
	if (!data->argv)
		error("analyse: organiser: data_argv_malloc");
	data->argv[lg] = NULL;
	while (*pouet)
	{
		data->argv[++j] = (*pouet)->content;
		*pouet = (*pouet)->next;
	}
	ft_lstclear(&first, do_nothing);
	return (end_parsing(str, i, data));
}
