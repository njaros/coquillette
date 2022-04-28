/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:03:39 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/28 15:55:24 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

t_list	*find_link(t_list *env, char *to_search)
{
	t_env	*var;

	var = NULL;
	while (env)
	{
		var = env->content;
		if (!ft_strcmp(var->name, to_search))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	env_del(t_list **env, t_list *to_del)
{
	t_list	*current;
	t_env	*var;

	current = NULL;
	if (*env == to_del)
		*env = (*env)->next;
	else
	{
		current = (*env);
		while (current->next && current->next != to_del)
			current = current->next;
	}
	if (current)
		current->next = to_del->next;
	var = to_del->content;
	free(to_del);
	free(var->name);
	free(var->value);
	free(var);
}

int	check_var_name(t_data *data, char *to_search)
{
	int	a;
	
	a = 0;
	if (!ft_isalpha(to_search[a]))
	{
		print_error(data, data->argv[1], "not a valid identifier", 1);
		return (1);
	}	
	while (to_search[a])
	{
		if (!ft_isalpha(to_search[a]) && !ft_isdigit(to_search[a]))
		{
			print_error(data, data->argv[1], "not a valid identifier", 1);
			return (1);
		}
		a++;
	}
	return (0);
}

int	built_unset(t_data *data)
{
	t_list	*tmp;
	int		i;

	data->last_return = 0;
	i = 1;
	while (data->argv[i])
	{
		if (!check_var_name(data, data->argv[i]))
		{
			tmp = find_link(data->env, data->argv[i]);
			if (tmp)
				env_del(&(data->env), tmp);
		}
		i++;
	}
	return (0);
}
