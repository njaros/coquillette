/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:44:27 by njaros            #+#    #+#             */
/*   Updated: 2022/05/03 09:08:55 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*set_color(char *str)
{
	char	*color;

	if (ft_strcmp(str, "ROUGE") == 0)
		color = ft_strdup("\e[31m");
	else if (ft_strcmp(str, "VERT") == 0)
		color = ft_strdup("\e[32m");
	else if (ft_strcmp(str, "JAUNE") == 0)
		color = ft_strdup("\e[33m");
	else if (ft_strcmp(str, "BLEU") == 0)
		color = ft_strdup("\e[34m");
	else if (ft_strcmp(str, "MAGENTA") == 0)
		color = ft_strdup("\e[35m");
	else if (ft_strcmp(str, "CYAN") == 0)
		color = ft_strdup("\e[36m");
	else if (ft_strcmp(str, "BLANC") == 0)
		color = ft_strdup("\e[37m");
	else
		color = ft_strdup("\e[34m");
	return (color);
}

char	*prompt_builder(t_data *data)
{
	char	*prompt;
	char	pwd[MAXPATHLEN];
	char	*color;
	char	*emoji;
	int		size;
	t_env	*env;

	emoji = NULL;
	color = NULL;
	env = find_env_var(data->env, "COLOR");
	if (env)
		color = set_color(env->value);
	else
		color = ft_strdup("\e[34m");
	(void)data;
	getcwd(pwd, MAXPATHLEN);
	size = ft_strlen("coquillette:> \e[0m") + 1;
	size += ft_strlen(pwd) + ft_strlen(color);
	env = find_env_var(data->env, "EMOJI");
	if (env)
		size += ft_strlen(env->value);
	prompt = ft_calloc(size, 1);
	ft_strcat(prompt, color);
	free(color);
	ft_strcat(prompt, "coquillette");
	if (env)
		ft_strcat(prompt, env->value);
	ft_strcat(prompt, ": ");
	ft_strcat(prompt, pwd);
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
	while (line_read && ft_strcmp(line_read, "es-tu parfait ?") == 0)
	{
		ft_putendl_fd("OUUUII je suis parfait 😘", 1);
		free(line_read);
		line_read = readline(prompt);
	}
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
	if (!line_read)
		data->last_return = 1;
	return (line_read);
}
