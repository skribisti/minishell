/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:43 by norabino          #+#    #+#             */
/*   Updated: 2025/05/14 19:33:29 by norabino         ###   ########.fr       */
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

void	ft_heredoc(char *end, char ***stockage, int *i)
{
	char *input;
	
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			break;
		if (ft_strcmp(input, end) == 0)
		{
			free(input);
			break;
		}
		*stockage = ft_realloc_tab(*stockage, *i + 1);
		if (!*stockage)
        {
            free(input);
            return;
        }
		(*stockage)[*i] = ft_strdup(input);
		printf("stockage[i]");
		if (!(*stockage[*i]))
		{
			free(input);
			(*stockage)[*i] = NULL;
			return ;
		}
		(*i)++;
		free(input);
	}
	if (*stockage)
		(*stockage)[*i] = NULL;
}

int	ft_parse_heredoc(t_minishell *command, int cmd_index, char *segment, int *begin_rdr, int *end_rdr)
{
	char **stockage;
	int	i;
	int	j;
	int	begin_hd;
	char **ends;

	begin_hd = 0;
	while (segment[begin_hd])
	{
   		if (segment[begin_hd] == '<')
    	{
        	*end_rdr = begin_hd;
        	while (segment[*end_rdr] && (segment[*end_rdr] == ' ' || segment[*end_rdr] == '<'))
            	(*end_rdr)++;
        	ft_set_spaces(segment, begin_hd, *end_rdr - begin_hd);
        	begin_hd = *end_rdr;
    	}
    	else
        	begin_hd++;
	}
	ends = ft_split(ft_substr(segment, *begin_rdr, ft_strlen(segment) - *begin_rdr), ' ');
	stockage = malloc(sizeof(char *) * 1);
	if (!stockage)
		return (ft_free_split(ends), 0);
	stockage[0] = NULL;
	i = 0;
	j = 0;
	while (ends[j])
	{
		ft_heredoc(ends[j], &stockage, &i);
		j++;
	}
	ft_free_split(ends);
	command->command_line[cmd_index].redirect.heredoc = stockage;
	return (i);
}

char **ft_realloc_tab(char **old, int new_size)
{
	char **new;
	int i;

	new = malloc((new_size + 1)* sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && old[i] && i < new_size - 1)
	{
		new[i] = ft_strdup(old[i]);
		free(old[i]);
		i++;
	}
	new[i] = NULL;
	free(old);
	return (new);
}