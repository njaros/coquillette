/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:51:29 by ccartet           #+#    #+#             */
/*   Updated: 2022/04/07 16:19:51 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	feel_free(t_list *env)
{
	t_env	*var;
	
	while (env)
	{
		var = env->content;
		free(var->name);
		free(var->value);
		env = env->next;
	}
}

long	ft_atol(const char *str)
{
	int		num;
	int		i;
	long	resultat;

	num = 1;
	i = 0;
	resultat = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			num = -num;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		resultat = resultat * 10 + (str[i] - '0');
		i++;
	}
	return (resultat * num);
}	

char	*ft_strmchr(char *s, char *charset)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
		{
			if (s[i] == charset[j])
				return (&s[i]);
			j++;
		}
		i++;
	}
	if (s[i] == charset[j])
		return (&s[i]);
	return (0);
}

int	print_err(char *str, int err)
{
	ft_putendl_fd(str, 2);
	g_cmd_ret = err;
	return (1);
}

t_env	*create_struct(char *env)
{
	t_env	*blop;

	blop = NULL;
	blop = malloc(sizeof(t_env));
	if (!blop)
		return (NULL);
	blop->name = ft_substr(env, 0, ft_strmchr(env, "=+") - env);
	if (ft_strrchr(env, '='))
		blop->eg = '=';
	else
		blop->eg = 'c';
	blop->value = ft_substr(ft_strchr(env, '='), 1, ft_strlen(env));
	blop->rank = 0;
	return (blop);
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
			return (NULL);
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_list;
	char	**cmd_arg;
	int		i;

	env_list = init_envp(envp);
	if (!env_list)
		return (1);
	cmd_arg = ft_split(argv[1], ' ');
	built_cd(cmd_arg, env_list, 1);
	i = 0;
	while (cmd_arg[i])
	{
		free(cmd_arg[i]);
		i++;
	}
	free(cmd_arg);
	feel_free(env_list);
	ft_lstclear(&env_list, del);
	return (0);
}