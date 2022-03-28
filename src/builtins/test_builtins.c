/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:20:47 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/28 14:49:03 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_err(char *str, int err)
{
	ft_putendl_fd(str, 2);
	g_cmd_ret = err;
	return (1);
}

char	*rl_get(char *line_read)
{
	if (line_read)
		free(line_read);
	line_read = readline("coquillette0.1>");
	if (!line_read)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	//line_read = check_quote_end(line_read);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

t_env	*find_env_var(t_list *env, char *to_search)
{
	t_env	*var;
	
	var = NULL;
	while (env)
	{
		var = env->content;
		if (!ft_strcmp(var->name, to_search))
			break ;
		env = env->next;
	}
	return (var);
}

t_env	*create_struct(char *env)
{
	t_env	*blop;

	blop = NULL;
	blop = malloc(sizeof(t_env));
	if (!blop)
		return (NULL);
	blop->name = ft_substr(env, 0, ft_strchr(env, '=') - env);
	//printf("%s\n", blop->name); voir pour laisser le = dans le name !!!
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

void	builtins(char **cmd_arg, t_list *env, int fd)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		built_echo(cmd_arg, fd);
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		built_cd(cmd_arg, env, fd);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		built_pwd(cmd_arg, fd);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		built_export(cmd_arg, env, fd);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		built_unset(cmd_arg, env);
	else if (!ft_strcmp(cmd_arg[0], "env"))
		built_env(env, cmd_arg, fd);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		built_exit(cmd_arg);
}

int	main(int argc, char ** argv, char **envp)
{
	t_list	*env_list;
	char	*line_read;
	char	**cmd_arg;

	line_read = NULL;
	env_list = init_envp(envp);
	if (!env_list)
		return (1);
	while (1)
	{
		line_read = rl_get(line_read);
		while (line_read)
		{
			printf("%s\n", line_read);
			free(line_read);
			line_read = NULL;
		}
		cmd_arg = ft_split(line_read, ' ');
		builtins(cmd_arg, env_list, 1);
		while (*cmd_arg++)
			free(*cmd_arg);
		free(cmd_arg);
	}
	return (0);
}
