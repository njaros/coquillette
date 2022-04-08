/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_doll_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:30:30 by njaros            #+#    #+#             */
/*   Updated: 2022/04/08 13:08:26 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*is_num_dollz(char *ret, char *str, int *ind, t_data *data)
{
	char	*number;
	char	*new;
	int		lg_nbr;

	if (str[ind[0] + 1] == '$')
		number = ft_itoa(getpid());
	else
		number = ft_itoa(data->last_return);
	lg_nbr = ft_strlen(number);
	new = ft_calloc(1, lg_nbr + ft_strlen(ret));
	if (!new)
	{
		free(number);
		return (NULL);
	}
	ft_strcat(new, ret);
	free(ret);
	ft_strcat(new, number);
	ind[0] += 2;
	ind[1] += lg_nbr - 1;
	return (new);
}

char	*is_str_dollz(char *ret, char *str, int *ind, t_data *data)
{
	int		lg_str;
	char	*to_search;
	char	*new;
	t_env	*env;

	to_search = ft_substr(str, ind[0] + 1, ind[2] - (ind[0] + 1));
	env = find_env_var(data->env, to_search);
	free(to_search);
	ind[0] = ind[2] - 1;
	if (!env)
		return (ret);
	lg_str = ft_strlen(env->value);
	new = calloc(1, lg_str + ft_strlen(ret) + 1);
	if (!new)
		return (NULL);
	ft_strcat(new, ret);
	free(ret);
	ft_strcat(new, env->value);
	ind[1] += lg_str;
	return (new);
}

int	handler_switcher(char c, char q)
{
	if (c != 34 && c != 39)
		return (q);
	if (!q)
		return (c);
	if (q == c)
		return (0);
	return (q);
}

char	*handler_doller(char *ret, char *str, int *ind, t_data *data)
{
	int	end;

	end = ind[0] + 1;
	if (str[ind[0] + 1] == '?' || str[ind[0] + 1] == '$')
		return (is_num_dollz(ret, str, ind, data));
	while (str[end] && !ft_metachar(str[end]))
		end++;
	ind[2] = end;
	return (is_str_dollz(ret, str, ind, data));
}

char	*quote_doll_handler(char *str, t_data *data)
{
	char	*ret;
	int		*ind;
	char	q_val;

	ind = malloc(sizeof(int) * 3);
	ret = ft_calloc(ft_strlen(str) + 1, 1);
	if (!ret)
		return (NULL);
	ind[0] = -1;
	ind[1] = -1;
	q_val = 0;
	while (str[++ind[0]])
	{
		q_val = handler_switcher(str[ind[0]], q_val);
		if (law_to_print(str[ind[0]], q_val, 1))
			ret[++ind[1]] = str[ind[0]];
		else if (str[ind[0]] == '$')
			ret = handler_doller(ret, str, ind, data);
	}
	free(ind);
	return (ret);
}