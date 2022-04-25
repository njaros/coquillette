/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:08:13 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/25 14:29:46 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	init_rank(t_list *env, int *size)
{
	t_env	*tmp;
	t_env	*actuel;
	t_list	*next;
	t_list	*env_bis;
	int		index;

	env_bis = env;
	while (env)
	{
		index = 1;
		actuel = env->content;
		next = env_bis;
		while (next)
		{
			tmp = next->content;
			if (ft_strcmp(actuel->name, tmp->name) > 0)
				index++;
			next = next->next;
		}
		actuel->rank = index;
		env = env->next;
		*size += 1;
	}
}

void	adding_value(t_env *var, char *value_bis)
{
	char	*tmp;
	
	tmp = NULL;
	tmp = ft_strjoin(var->value, value_bis);
	if (!tmp)
		error("malloc");
	free(var->value);
	var->value = ft_strdup(tmp);
	if (!var->value)
		error("malloc");
	free(tmp);
}

int	replace_or_create(t_list *env, t_env *var, char *name, char *value)
{
	t_list	*new;

	new = NULL;
	if (!var)
	{
		new = ft_lstnew(create_struct(name));
		if (!new)
			error("lst problem");
		ft_lstadd_back(&env, new);
	}
	else
	{
		if (ft_strrchr(name, '+'))
		{
			adding_value(var, value);
			return (0);
		}
		if (ft_strrchr(name, '='))
			var->eg = '=';
		free(var->value);
		var->value = ft_strdup(value);
		if (!var->value)
			error("malloc");
	}
	return (0);
}

t_env	*find_env_var(t_list *env, char *to_search)
{
	t_env	*var;

	var = NULL;
	while (env)
	{
		var = env->content;
		if (!ft_strcmp(var->name, to_search))
			return (var);
		env = env->next;
	}
	return (NULL);
}
