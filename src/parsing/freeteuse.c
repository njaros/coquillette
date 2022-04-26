/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeteuse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:00:25 by njaros            #+#    #+#             */
/*   Updated: 2022/04/26 11:38:28 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

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
