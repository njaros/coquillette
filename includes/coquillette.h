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
	char	*name;
	char	eg;
	char	*value;
	int		rank;
}				t_env;

typedef struct s_data
{
	int		last_return;
	int		nb_cmd;
	int		in;
	int		out;
	char	**argv;
	t_list	*env;
}				t_data;

// Gestion initiales de l'entrée utilisateur

void	terminal_handler(int end);
void	signal_handler(int sig, siginfo_t *siginfo, void *ucontext);
void	reset_readline(void);
char	*prompt_builder(t_data *data);
char	*rl_get(char *line_read, t_data *data);

// Fonctions d'initialisation

void	init_data(t_data *data, int i, char *str);
void	init(struct sigaction *act, t_data *data, t_list *env);

// ICI ON PARSE
// check_quote
char	*check_quote_end(char *str);
int		double_token_char(char *str, int *quote, int *dquote, int *i);
char	*guilty_searcher(char *str, int *quote, int *dquote);
// check_quote2
void	le_coupable_est(char *c);
int		first_char_is_pipe(char *str, int *i);
int		last_char_is_pipe(char *str);
int		ft_tokenchar(int c);
int		ft_metachar(int c);
// analyse
void	do_nothing(void *let_him_alive);
int		ajout_block(t_list **pouet, int *i, int *ptr, char *str);
int		analyse(char *str, int *i, t_data *data);
// analyse2
int		lst_dequotage(t_list *lst, t_data *data);
int		end_parsing(char *str, int *i, t_data *data);
int		organiser(t_list **pouet, int *i, char *str, t_data *data);
// analyse_utils
int		count_pipe(char *str);
void	init_data(t_data *data, int i, char *str);
void	init_analyse(char *str, int *i, int *ptr);
void	quote_switcher(int *quote, int *dquote, char c);
int		analyse_sep(char *str, int *i, int context);
// chevron
int		chevronnage(t_list **pouet, t_data *data);
int		chevron_manager(t_list **pouet, t_list *prev, t_data *data);
int		manip_chevron_str(char **str);
void	file_to_open(char *file, int chev, t_data *data);
// heredoc
char	*heredoc_handler(char *str);
void	heredoc_fork(int fd, char *end);
char	*parse_heredoc(char *str, int *i);
int		is_heredoc(char *str, int quote, int dquote);
char	*ft_heredoc(char *eof);
char	*signaled_heredoc(int fd_in, int fd_out);
// quote_doll_handler
char	*quote_doll_handler(char *str, t_data *data);
char	*handler_doller(char *ret, char *str, int *ind, t_data *data);
int		handler_switcher(char c, char q);
char	*is_str_dollz(char *ret, char *str, int *ind, t_data *data);
char	*is_num_dollz(char *ret, int *ind, t_data *data);
// quote_doll_handler2
char	*only_quote_handler(char *str);
int		law_to_print(char a, char q, char b);
int		trap_dollz(char b);

//EN DESSOUS ON NE PARSE PAS

int		free_lst_analyse(t_list **to_free);
int		error2(int err);

// coquilette_utils
t_list	*init_envp(char **envp);
t_env	*create_struct(char *envp);
void	feel_free(void *env);
void	ft_free(char **tab);
void	print_error(t_data *data, char *arg, char *msg, int err);

// EXECUTION //
// execution
void	execution(char *line_read, t_data *data);
pid_t	*exec_cmd(t_data *data, char *line_read, int *i);
int		create_process(t_data *data, int pipefd[2], int *fd_in, int j);
void	child(t_data *data, int pipefd[2]);
void	recover_status(t_data *data, pid_t *f_pid);
// exec_utils
int		do_builtins(t_data *data);
int		check_is_builtin(t_data *data);
void	transform_fds(t_data *data, int fd_in, int fd_out);
char	**list_to_tab(t_list *env);
void	error(char *msg);
// found_cmd
char	*found_cmd(t_data *data, char *entry, t_list *env);
int		check_absolute_path(t_data *data, char *entry);
int		is_a_directory(t_data *data, char *entry);
char	*get_path(char *cmd, char **path);

// BUILTINS //
// builtins_utils
t_env	*find_env_var(t_list *env, char *to_search);
int		replace_or_create(t_list *env, t_env *var, char *name, char *value);
void	adding_value(t_env *var, char *value_bis);
void	init_rank(t_list *env, int *size);
// built_cd
int		built_cd(t_data *data);
int		to_home(t_data *data, char c);
int		dash(t_data *data);
int		move_to(t_data *data);
void	change_pwd_oldpwd(char *oldpwd, t_list *env);
// built_echo
int		built_echo(t_data *data);
void	print_echo(t_data *data, int i);
// built_env
int		built_env(t_data *data);
void	print_env(t_data *data, t_env *tmp);
// built_exit
int		built_exit(t_data *data);
int		check_arg(char *arg);
// built_export
int		built_export(t_data *data);
int		export_alone(t_data *data);
char	*set_to_search(t_data *data, int i);
void	print_export(t_list *env, int size, int fd);
void	print(t_env *tmp, int fd);
// built_pwd
int		built_pwd(t_data *data);
// built_unset
int		built_unset(t_data *data);
t_list	*find_link(t_list *env, char *to_search);
void	env_del(t_list *env, t_list *to_del);

#endif