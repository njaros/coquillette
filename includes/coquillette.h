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
	int		in;
	int		out;
	char	**argv;
    char	*cmd_path;
}	            t_data;

typedef struct s_pipe
{
    int     infile;
    int     outfile;
    char    **path;
    char    **cmd1_arg;
    char    *cmd1;
    char    **cmd2_arg;
    char    *cmd2;
}               t_pipe;

// Gestion initiales de l'entrée utilisateur

void	handler(int sig, siginfo_t *siginfo, void *ucontext);
char	*rl_get(char *line_read);

// Fonctions d'initialisation

void 	init_data(t_data *data, int i);
void	init_sigact(struct sigaction *act);

// Fonctions utiles pour tout le cursus (bonne idée de les intégrer à la libft)

int		get_fd_rdonly(char *entry);
int		ft_tokenchar(int c);
int		ft_metachar(int c);
int		ft_switch(int n);
t_list	*ft_lsttake(t_list **alst);

// ICI ON PARSE
void	debug_blocs(t_list *lst); // Debbugger
char	*quotage(char *str, int *dquote, int *quote);
char	*pipage(char *str);
char	*check_quote_end(char *str);
char	*replace_dollz(char *str, int *i, int end);
int		ft_quote_switch(int quote, char c);
char	*dollar_searcher(char *str);
int		double_token_char(char *str, int *quote, int *dquote, int *i);
int		alone_pipe(char *str, int *i);
char	*cherche_merde(char *str, int *quote, int *dquote);
void	le_coupable_est(char *c);
int		analyse(char *str, int *i, t_data *data);
int		ajout_block(t_list **pouet, int *i, int *ptr, char *str);
char	*dollz_what(char *str, t_data *data);
char	*last_return(char *str, int *i, int ret);
int		chevronnage(t_list **pouet, t_data *data);
int		chevron_manager(t_list **pouet, t_list *prev, t_data *data);
int		manip_chevron_str(char **str);
void	file_to_open(char *file, int chev, t_data *data);
void	reorder_lst(t_list **lst, t_list *prev);
void	analyse_error_message(char *str, int context);
int		analyse_sep(char *str, int *i, int context);
void	init_analyse(char *str, int *i, int *ptr);
void	quote_switcher(int *quote, int *dquote, char c);
int		organiser(t_list **pouet, int *i, char *str, t_data *data);

//pipe
int     pipex(int argc, char *argv[], char **envp);
void    init(t_pipe *pip, char **argv);
void    child_one(t_pipe *pip, int *fd, char **envp);
void    child_two(t_pipe *pip, int *fd, char **envp);
char    *get_cmd(char *cmd, char **path);
//
void    feel_free(t_pipe *pip);
void	ft_free(char **tab);
int		free_lst_analyse(t_list **to_free);
void	error(char *msg);
int		error2(int err);

//coquilette_utils1
t_env	*find_env_var(t_list *env, char *to_search);
t_list	*init_envp(char **envp);
t_env	*create_struct(char *envp);
char	*ft_strmchr(char *s, char *charset);

// multipipe
void	test_exec(char *line_read, t_list *env);
int	    loop_pipe(t_data *data, int fd_in, int pipefd[2], t_list *env);
char	*found_cmd(char *entry);

#endif