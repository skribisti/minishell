/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:43 by norabino          #+#    #+#             */
/*   Updated: 2025/05/13 17:41:06 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_parse_heredoc(t_minishell *command, int cmd_index, char *segment, int begin_rdr, int end_rdr)
{
	if (ft_cpt_heredoc(segment) == 1)
		command->command_line[cmd_index].redirect.heredoc = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
}


void	ft_heredoc(char *end)
{
	char *input;
	char **stockage;
	int	i;

	i = 0;
	stockage = malloc(sizeof(char *) * 1);
	if (!stockage)
		return ;
	stockage[0] = NULL;
	while (1)
	{
		input = readline(NULL);
		if (*input)
		{
			if (ft_strcmp(stockage[i], end))
			{
				if (i >= ft_strstrlen(stockage))
					ft_realloc_tab(stockage, ft_strstrlen(stockage));
				if (i < ft_strstrlen(stockage));
				stockage[i] = ft_strdup(input);
			}
			else
				break;
		}
	}
}

char **ft_realloc_tab(char **old, int new_size)
{
	char **new;
	int i;

	new = malloc(new_size * sizeof(char *) + 1);
	if (!new)
		return NULL;
	i = 0;
	while (old && old[i] && i < new_size)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	free(old);
	return new;
}