/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:58:06 by njaros            #+#    #+#             */
/*   Updated: 2022/04/05 09:33:38 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	fill_without_quote(char *fill, char * str, int begin, int end)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str[++i])
		if (i != begin && i != end)
			fill[++j] = str[i];
	free(str);
}

int	str_dequotage(char *str, t_list *lst)
{
	char	*no_quote;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != 34 && str[i] != 39)
		i++;
	if (!str[i])
		return (1);
	j = ft_strlen(str);
	no_quote = ft_calloc(1, j - 1);
	if (!no_quote)
		return (0);
	while (j >= 0 && str[j] != 34 && str[j] != 39)
		j--;
	fill_without_quote(no_quote, str, i, j);
	lst->content = no_quote;
	return (1);
}

int	lst_dequotage(t_list *lst)
{
	char	*content;

	while (lst)
	{
		content = lst->content;
		if (!str_dequotage(content, lst))
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	organiser(t_list **pouet, int *i, char *str, t_data *data)
{
	t_list	*first;
	int		lg;
	int		j;

	j = -1;
	lg = chevronnage(pouet, data);
	if (!lst_dequotage(*pouet))
		return (free_lst_analyse(pouet));
	first = *pouet;
	data->argv = malloc(sizeof(char *) * lg + 1);
	if (!data->argv)
		return (free_lst_analyse(pouet));
	data->argv[lg] = NULL;
	while (*pouet)
	{
		data->argv[++j] = (*pouet)->content;
		*pouet = (*pouet)->next;
	}
	if (str[*i] == '|')
	{
		*i += 1;
		return (1);
	}
	if (data->out == -2)
		data->out == 1;
	return (0);
}