/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:44:27 by njaros            #+#    #+#             */
/*   Updated: 2022/04/27 17:24:56 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*prompt_builder(t_data *data)
{
	char	*prompt;
	t_env	*env;
	int		size;

	env = find_env_var(data->env, "PWD");
	size = ft_strlen("\e[34mcoquillette:> \e[0m") + 1;
	if (env)
		size += ft_strlen(env->value);
	prompt = ft_calloc(size, 1);
	ft_strcat(prompt, "\e[34mcoquillette: ");
	if (env)
		ft_strcat(prompt, env->value);
	ft_strcat(prompt, ">\e[0m");
	return (prompt);
}

char	*rl_get(char *line_read, t_data *data)
{
	char	*prompt;

	prompt = prompt_builder(data);
	if (line_read)
		free(line_read);
	line_read = readline(prompt);
	free(prompt);
	if (!line_read)
	{
		terminal_handler(1);
		feel_free(data->env);
		ft_lstclear(&(data->env), del);
		ft_putendl_fd("exit", 1);
		exit(WEXITSTATUS(data->last_return));
	}
	line_read = check_quote_end(line_read);
	if (line_read && *line_read)
	{
		add_history(line_read);
		line_read = heredoc_handler(line_read);
	}
	return (line_read);
}
