/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeteuse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:00:25 by njaros            #+#    #+#             */
/*   Updated: 2022/04/25 09:45:45 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

int	free_lst_analyse(t_list **to_free)
{
	ft_lstclear(to_free, free);
	return (0);
}

void	feel_free(void *env)
{
	t_list	*envv;
	t_env	*var;

	envv = env;
	while (envv)
	{
		var = envv->content;
		free(var->name);
		free(var->value);
		envv = envv->next;
	}
}
