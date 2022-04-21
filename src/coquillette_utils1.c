/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coquillette_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:20:42 by njaros            #+#    #+#             */
/*   Updated: 2022/03/08 16:46:37 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd("coquillette: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(NULL);
}

int	print_err(char *str, int err)
{
	ft_putendl_fd(str, STDERR_FILENO);
	g_cmd_ret = err;
	return (1);
}

t_env	*create_struct(char *env)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_substr(env, 0, ft_strmchr(env, "=+") - env);
	if (ft_strrchr(env, '='))
		new->eg = '=';
	else
		new->eg = 'c';
	new->value = ft_substr(ft_strchr(env, '='), 1, ft_strlen(env));
	new->rank = 0;
	return (new);
}

t_list	*init_envp(char **envp)
{
	t_list	*env;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	env = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(create_struct(envp[i]));
		if (!tmp)
		{
			ft_lstclear(&env, del);
			return (NULL);
		}
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}
