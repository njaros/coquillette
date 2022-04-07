/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:03:39 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/06 15:02:21 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

t_list	*find_link(t_list *env, char *to_search)
{
	t_list	*link;
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

void	env_del(t_list *env, t_list *to_del)
{
	t_list	*current;
	t_env	*var;
	
	current = env;
	while(current)
	{
		if (current->next == to_del)
		{
			current->next = to_del->next;
			break ;
		}
		current = current->next;
	}
	var = to_del->content;
	free(var->name);
	free(var->value);
	free(var);
}

int	built_unset(char **cmd_arg, t_list *env)
{
	t_list	*tmp;
	int		i;
	
	i = 1;
	while (cmd_arg[i])
	{
		tmp = find_link(env, cmd_arg[i]);
		if (tmp)
			env_del(env, tmp);
		i++;
	}
	return (0);
}
