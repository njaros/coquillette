/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:42:30 by ccartet           #+#    #+#             */
/*   Updated: 2022/03/25 11:16:07 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coquillette.h"

int	ft_strcmp(char *s1, char *s2)
{
    int	i;

    i = 0;
    while (s1[i] || s2[i])
    {
        if (!(s1[i] == s2[i]))
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (0);
}

void	builtins(char **cmd_arg)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		built_echo
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		built_cd(cmd_arg, env);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		built_pwd(fd);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		built_export(cmd_arg, fd);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		built_unset
	else if (!ft_strcmp(cmd_arg[0], "env"))
		built_env(env, fd);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		built_exit(cmd_arg, fd);
}

void	built_echo(char **cmd_arg, int fd)
{
	int		nl;
	int		i;
	char	*new;

	nl = 1;
	i = 1;
	if (!ft_strncmp(cmd_arg[i], "-n", 2)) // vérifier si après - on a bien un n
	{
		n = 0;
		i++;
	}
	new = dollar_searcher(cmd_arg[i]);
	ft_putstr_fd(new, fd);
	if (nl)
		ft_putchar_fd('\n', fd);
} // vérifier si echo s'arrete bien quand il y a un espace, qu'est ce qu'il fait s'il y a un \n
// sinon while avec putchar espace
void	built_export(char **cmd_arg, t_list *env)
{
	t_env	*tmp;
	t_list	*new;
	int		ok;
 // vérifier si l'arguement entré est valable, s'il y a un =, que fait export NAME (sans =, sans rien après) ?
	// attention possibilité de créer plusieurs variables en même temps !!
	ok = 0;
	while (env) // créer fonction qui recherche la variable d'environnement !!
	{
		tmp = env->content;
		if (!ft_strncmp(cmd_arg[1], tmp->name, ft_strlen(tmp->name)))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_substr(ft_strchr(cmd_arg[1], '='), 1, ft_strlen(cmd_arg[1]));
			ok = 1;
		}
		env = env->next;
	}
	if (!ok)
	{
		new = ft_lstnew(create_struct(cmd_arg[1]));
		if (!new)
			return (NULL);
		ft_lstadd_back(&env, new);
	}
} // que fait export tout court ?!

void	built_unset(char **cmd_arg, t_list *env) // méthode faignasse
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->content;
		if (!ft_strncmp(cmd_arg[1], tmp->name, ft_strlen(tmp->name)))
		{
			free(tmp->value);
			tmp->value = NULL;
			return ;
		}
		env = env->next;
	}
}

void	built_unset_v2(char **cmd_arg, t_list *env)
{
	t_env	*tmp;
	t_list	*previous;
	t_list	*current;
// vérifier si l'argument est un mot, espace ?
	previous = env;
	while (env)
	{
		current = env;
		tmp = current->content;
		if (!ft_strncmp(cmd_arg[1], tmp->name, ft_strlen(tmp->name)))
		{
			previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			current = NULL;
		}
		previous = current;
		env = env->next;
	}
} // attention, possibilité de supprimer plusieurs variables en même temps !!

void	built_cd(char **cmd_arg, t_list *env)
{
	char	*home;
	t_env	*tmp;
	char	*pwd;
 // créer une fonction qui va chercher lune varaiable spécifique dans ma liste chainée env : find_env_var(struct, nom de la variable)
	pwd = getcwd(NULL, 0); // vérifier retour de getcwd => getcwd(cwd, MAXPATHLEN) ?
	home = getenv("HOME"); // vérifier si home existe, et si elle n'existe pas message d'erreur, tester lancemenet shell avec env -i, cd : home not set
	if (!cmd_arg[1])
		chdir(home);
	else
	{
		if (!ft_strcmp(cmd_arg[1], "~"))
			chdir(home);
		else if (chdir(cmd_arg[1]) == -1)
			perror("cd");
	}
	while (env)
	{
		tmp = env->content;
		if (!ft_strcmp(tmp->name, "PWD")) // vérifier si pwd existe, si oui free l'ancienne valeur
			tmp->value = getcwd(NULL, 0);
		if (!ft_strcmp(tmp->name, "OLDPWD"))
			tmp->value = pwd;
		env = env->next;
	} // attention à stocker les erreurs de chaque appel de fonction !
}

void	built_pwd(int fd)
{
	char	*pwd;
 // vérifier s'il y a trop d'arguments
	// if (getcwd(pwd, sizeof(pwd) == NULL)
	// 	perror("getcwd() error");
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
}

void	built_env(t_list *env, int fd)
{
	t_env	*tmp;
// vérifier qu'il n'y pas trop d'arguments sinon "too many arguments"
	while (env)
	{
		tmp = env->content;
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(tmp->value, fd);
		}
		env = env->next;
	}
}

void	built_exit(char **cmd_arg, int fd)
{
	int	i;

	if (!cmd_arg[1])
	{
		ft_putendl_fd("exit", 2);
		// fonction feel_free
		exit(cmd_ret); // code erreur enregsitré dans struct globale + free
	}
	else // verifier aussi sir le nb est compris entre 0 et ..., si c'est un code erreur
	{
		i = 0;
		while(cmd_arg[1][i])
		{
			if (ft_isdigit(cmd_arg[1][i]))
				i++;
			else
				return ; // "numeric argument required" et "exit" avec code erreur 255 ? ou trop d'arguments
		}
		ft_putendl_fd("exit", 2);
		exit(ft_atoi(cmd_arg[1])); // + fonction feel_free
	}
}