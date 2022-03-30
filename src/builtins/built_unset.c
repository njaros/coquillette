/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:03:39 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/30 10:56:23 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	built_unset(char **cmd_arg, t_list **env)
{
	t_env	*tmp;
	t_list	*previous;
	t_list	*current;
	int		out;
	int		i;

	out = 0;
	previous = *env;
	while (*env)
	{
		current = *env;
		tmp = current->content;
		i = 0;
		while (cmd_arg[i++])
		{
			if (!ft_strncmp(cmd_arg[i], tmp->name, ft_strlen(tmp->name)))
			{
				out = 1;
				break ;
			}
		}
		if (out)
		{
			previous->next = current->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			current = NULL;
		}
		previous = current;
		*env = (*env)->next;
	}
}
// attention tester d'unset deux variables l'une après l'autre, si y en a pas une qui est ignorée...

// void	built_unset_v2(char **cmd_arg, t_list *env)
// {
// 	t_env	*tmp;
// 	int		i;
	
// 	i = 1;
// 	while (cmd_arg[i])
// 	{
// 		tmp = find_env_var(env, cmd_arg[i]);
		
		
// 		i++;
// 	}
	
// }
// tester avec find_env_var et fonction Nicolas pour enlever un maillon !
