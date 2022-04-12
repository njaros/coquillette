/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coquillette.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:21:14 by njaros            #+#    #+#             */
/*   Updated: 2022/03/08 16:46:52 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COQUILLETTE_H
# define COQUILLETTE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <fcntl.h>
# include "libft.h"

// Toutes les structures utilisées par coquillette

typedef struct s_env
{
    char    *name;
    char    eg;
    char    *value;
	int		rank;
}               t_env;

typedef struct s_data
{
	int		last_return;
    int     nb_cmd; //(= nbr de pipes hors des quote + 1)
	int		in;
	int		out;
	char	**argv;
	char	*cmd_path;
	t_list	*env;
}	            t_data;

long	g_cmd_ret;

// Gestion initiales de l'entrée utilisateur

void	handler(int sig, siginfo_t *siginfo, void *ucontext);
char	*rl_get(char *line_read, int cmd_return);

// Fonctions d'initialisation

void 	init_data(t_data *data, int i, char *str);
void	init_sigact(struct sigaction *act);

// ICI ON PARSE
void	do_nothing(void *let_him_alive);
char	*eof_detector(char *to_free, int context);
char	*quotage(char *str, int *dquote, int *quote);
char	*pipage(char *str);
char	*check_quote_end(char *str);
int		double_token_char(char *str, int *quote, int *dquote, int *i);
int		first_char_is_pipe(char *str, int *i);
int		last_char_is_pipe(char *str);
char	*cherche_merde(char *str, int *quote, int *dquote);
void	le_coupable_est(char *c);
int		analyse(char *str, int *i, t_data *data);
int		ajout_block(t_list **pouet, int *i, int *ptr, char *str);
int		chevronnage(t_list **pouet, t_data *data);
int		chevron_manager(t_list **pouet, t_list *prev, t_data *data);
int		manip_chevron_str(char **str);
void	file_to_open(char *file, int chev, t_data *data);
int		analyse_sep(char *str, int *i, int context);
void	init_analyse(char *str, int *i, int *ptr);
void	quote_switcher(int *quote, int *dquote, char c);
int		organiser(t_list **pouet, int *i, char *str, t_data *data);
int		ft_tokenchar(int c);
int		ft_metachar(int c);
int		ft_switch(int n);
char	*quote_doll_handler(char *str, t_data *data);
char	*only_quote_handler(char *str);
int		handler_switcher(char c, char q);
int		law_to_print(char a, char q, int context);

//
int		free_lst_analyse(t_list **to_free);
int		error2(int err);

//coquilette_utils1
t_list	*init_envp(char **envp);
t_env	*create_struct(char *envp);
int	    print_err(char *str, int err);
void	feel_free(t_list *env);

// execution
int		execution(char *line_read, t_list *env);
void    fork_loop(t_data *data, int pipefd[2], t_list *env, int *fd_in);
void	transform_fds(t_data *data, int fd_in, int fd_out);
char	*found_cmd(char *entry, t_list *env);
char    *get_path(char *cmd, char **path);
char    **list_to_tab(t_list *env);
void	ft_free(char **tab);
void	error(char *msg);
//test
void	test_exec(char *line_read, t_list *env);
void    loop_pipe(t_data *data, int *fd_in, int pipefd[2], t_list *env);

// builtins
int	    builtins(t_data data, t_list *env);
//
int	    built_cd(char **cmd_arg, t_list *env, int fd);
int	    to_home(char c, t_list *env);
int 	change_pwd_oldpwd(char *oldpwd, t_list *env);
int 	replace_or_create(t_list *env, t_env *var, char *var_name, char *path);
t_env	*find_env_var(t_list *env, char *to_search);
//
int 	built_echo(char **cmd_arg, int fd);
//
int	    built_env(t_list *env, char **cmd_arg, int fd);
//
void	built_exit(char **cmd_arg, t_list *env);
int	    check_arg(char *arg);
//
int	    built_export(char **cmd_arg, t_list *env, int fd);
void	print_export(t_list *env, int size, int fd);
void    init_rank(t_list *env, int *size);
//
int 	built_pwd(char **cmd_arg, int fd);
//
int 	built_unset(char **cmd_arg, t_list *env);
t_list	*find_link(t_list *env, char *to_search);
void	env_del(t_list *env, t_list *to_del);

#endif