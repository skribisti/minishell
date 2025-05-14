/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:50 by norabino          #+#    #+#             */
/*   Updated: 2025/05/14 15:54:00 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_nextpipe(char *line, int last_pipe)
{
	while (line[last_pipe] && line[last_pipe] != '|')
		last_pipe++;
	return (last_pipe);
}

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_set_spaces(char *segment, int begin, int length)
{
    int	i;

    i = 0;
    while (i < length && segment[begin + i])
    {
        segment[begin + i] = ' ';
        i++;
    }
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_cpt_heredoc(char *segment)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (segment[i])
	{
		if (segment[i] == '<' && segment[i + 1] == '<')
		{
			cpt++;
			i += 2;
		}
		else
			i++;
	}
	return (cpt);
}
