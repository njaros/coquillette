/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coquillette.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:47:13 by njaros            #+#    #+#             */
/*   Updated: 2022/03/08 16:57:51 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

t_list	*create_backup_list(void)
{
	t_list	*env_list;
	char	**backup_list;
	char	pwd[MAXPATHLEN];

	backup_list = NULL;
	backup_list = malloc(sizeof(char *) * 3);
	if (!backup_list)
		error("main: backup_list");
	getcwd(pwd, MAXPATHLEN);
	backup_list[0] = ft_strjoin("PWD=", pwd);
	backup_list[1] = ft_strdup("SHLVL=1");
	backup_list[2] = NULL;
	env_list = init_envp(backup_list);
	if (!env_list)
		error("main: env_list");
	return (env_list);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	act;
	char				*line_read;
	t_list				*env_list;
	t_data				data;

	(void)argc;
	(void)argv;
	env_list = init_envp(envp);
	if (!env_list)
		env_list = create_backup_list();
	init(&act, &data, env_list);
	kill(0, SIGUSR2);
	line_read = NULL;
	while (1)
	{
		terminal_handler(0);
		line_read = rl_get(line_read, &data);
		terminal_handler(1);
		if (line_read)
			execution(line_read, &data);
	}
	ft_lstclear(&env_list, feel_free);
	return (0);
}
