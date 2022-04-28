/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:44:27 by njaros            #+#    #+#             */
/*   Updated: 2022/04/28 15:40:18 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

char	*prompt_builder(t_data *data)
{
	char	*prompt;
	char	pwd[MAXPATHLEN];
	int		size;
	
	(void)data;
	getcwd(pwd, MAXPATHLEN);
	size = ft_strlen("\e[34mcoquillette:> \e[0m") + 1;
	size += ft_strlen(pwd);
	prompt = ft_calloc(size, 1);
	ft_strcat(prompt, "\e[34mcoquillette: ");
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
