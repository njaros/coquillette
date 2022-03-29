/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ajout1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:55:34 by njaros            #+#    #+#             */
/*   Updated: 2022/03/10 13:42:41 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coquillette.h"

//get_fd retourne atoi(entry) si entry est seulement composé de chiffres,
//sinon il retourne en read_only le fd du fichier du même nom s'il existe.

int	get_fd_rdonly(char *entry)
{
	int	i;
	int	fd;

	i = -1;
	while (entry[++i])
	{
		if (entry[i] < '0' && entry[i] > '9')
			return (open(entry, O_RDONLY));
	}
	fd = open(entry, O_RDONLY);
	if (fd < 0)
		return (ft_atoi(entry));
	else
		return (fd);
}

int	ft_switch(int n)
{
	if (n)
		return (0);
	return (1);
}

// ft_lsttake prend retire un maillon d'une liste, puis met le next de ce maillon à NULL, puis retourne ce maillon
// le pointeur de la liste qui a perdu son maillon passe au next, attention à la perte de données

int	ft_metachar(int c)
{
	if (c >= 32 && c <= 47)
		return (1);
	if (c >= 58 && c <= 64)
		return (1);
	if ((c >= 91 && c <= 94) || c == 96)
		return (1);
	if (c >= 123 && c <= 125)
		return (1);
	return (0);
}

int	ft_tokenchar(int c)
{
	if (c == '\n')
		return (1);
	if (c == ';')
		return (1);
	if (c == '&')
		return (1);
	if (c == '|')
		return (1);
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

t_list	*ft_lsttake(t_list **alst)
{
	t_list	*token;

	if (!*alst)
		return NULL;
	token = *alst;
	*alst = (*alst)->next;
	token->next = NULL;
	return (token);
}
