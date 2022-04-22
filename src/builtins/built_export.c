/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:17:08 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/22 15:15:51 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

static void	print(t_env *tmp, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(tmp->name, fd);
	if (tmp->value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	print_export(t_list *env, int size, int fd)
{
	t_env	*tmp;
	t_list	*env_tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (i <= size)
	{
		env_tmp = env;
		while (env_tmp)
		{
			tmp = env_tmp->content;
			if (tmp->rank == i)
			{
				print(tmp, fd);
				break ;
			}
			env_tmp = env_tmp->next;
		}
		i++;
	}
}

char	*set_to_search(t_data *data, int i)
{
	int		a;
	char	*to_search;
	int		len;

	a = -1;
	len = ft_strmchr(data->argv[i], "=+") - data->argv[i];
	to_search = ft_substr(data->argv[i], 0, len);
	if (!to_search)
		to_search = ft_strdup(data->argv[i]); // à vérifier ?
	if (to_search[0] == '\0')
	{
		print_error(data, data->argv[1], "not a valid identifier", 1);
		return (NULL);
	}
	while (to_search[a++])
	{
		if (!ft_isdigit(to_search[a]))
		{
			print_error(data, data->argv[1], "not a valid identifier", 1);
			return (NULL);
		}
	}
	return (to_search);
}

int	export_alone(t_data *data)
{
	int	size_env;

	size_env = 0;
	if (data->out == -1)
	{
		data->last_return = 1;
		return (1);
	}
	if (!data->argv[1])
	{
		init_rank(data->env, &size_env);
		print_export(data->env, size_env, data->out);
	}
	return (0);
}

int	built_export(t_data *data)
{
	int		i;
	t_env	*tmp;
	char	*to_search;
	char	*value;
	int		size;

	data->last_return = 0;
	i = 1;
	size = 0;
	if (export_alone(data))
		return (1);
	while (data->argv[i])
	{
		to_search = set_to_search(data, i);
		if (!to_search)
			return (1);
		tmp = find_env_var(data->env, to_search);
		free(to_search);
		size = ft_strlen(data->argv[i]);
		value = ft_substr(ft_strchr(data->argv[i], '='), 1, size);
		replace_or_create(data->env, tmp, data->argv[i], value);
		i++;
	}
	return (0);
}
