/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:54:39 by norabino          #+#    #+#             */
/*   Updated: 2025/05/16 19:02:20 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(char *str)
{
	char	*tab;
	int		i;

	if (!str)
		return (NULL);
	tab = (char *)malloc(ft_strlen(str) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	*ft_handle_meta_chars(char *prompt, int begin)
{
	int		i;
	int		size;
	char	*string;
	
	i = begin;
	while (prompt[i] != 34 && prompt[i] != 39)
		i++;
	size = i - begin;
	string = ft_substr(prompt, begin, size);
	if (!string)
		return (NULL);
	return (string);
}

int	ft_ind_firstspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	ft_nbpipes(char *line)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (line[i])
	{
		if (line[i] == '|')
			cpt++;
		i++;
	}
	return (cpt);
}