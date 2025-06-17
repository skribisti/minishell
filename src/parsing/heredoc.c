/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:34 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/17 17:30:19 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	readline_heredoc(t_minishell *minishell, char *delimiter, int cmd_idx)
{
	char *input;

	free(minishell->command_line[cmd_idx].redirect.ri);
	minishell->command_line[cmd_idx].redirect.ri = NULL;
	free(minishell->command_line[cmd_idx].redirect.heredoc);
	minishell->command_line[cmd_idx].redirect.heredoc = ft_strdup("");
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			return (write(2, "minishell: warning: here-document end-of-file\n", 46), 0);
		if (!ft_strcmp(input, delimiter))
			return (free(input), 0);
		minishell->command_line[cmd_idx].redirect.heredoc = ft_join_free(ft_join_free(minishell->command_line[cmd_idx].redirect.heredoc, input), "\n");
		free(input);
	}
	return (1);
}

/*
void ft_heredoc(char **delimiters, char ***stockage, int *i)
{
    int current_end;
	int	end_count;
   
	current_end = 0;
	end_count = ft_strstrlen(delimiters);
    while (delimiters[current_end])
    {
        *i = 0;
        if (*stockage)
		{
            ft_free_split(*stockage);
			*stockage = NULL;
		}
        *stockage = malloc(sizeof(char *) * 1);
        if (!*stockage)
            return;
        (*stockage)[0] = NULL;
		if (!readline_heredoc())
			return;
        current_end++;
    }
    if (*stockage)
        (*stockage)[*i] = NULL;
}



int	ft_parse_heredoc(t_minishell *minishell, int cmd_index, char *segment, int *begin_rdr, int *end_rdr)
{
	char **stockage;
	int	i;
	int	begin_hd;
	char **delimiters;	
	int	cpt_delimiter;
	int	j;
	int	pos;
	char	*substr;

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
	pos = *begin_rdr;
	substr = ft_substr(segment, *begin_rdr, ft_strlen(segment) - *begin_rdr);
	delimiters = ft_split_line(substr, ' ');
	free(substr);
	if (!delimiters)
		return (0);
	minishell->command_line[cmd_index].redirect.hd_delimiters = delimiters;
	stockage = malloc(sizeof(char *));
	if (!stockage)
		return (ft_free_split(delimiters), 0);
	stockage[0] = NULL;
	i = 0;
	ft_heredoc(delimiters, &stockage, &i);
	cpt_delimiter = ft_strstrlen(delimiters);
	if (cpt_delimiter > 0)
	{
		j = 0;
		while (j < cpt_delimiter)
		{
			while (segment[pos] && segment[pos] == ' ')
				pos++;
			pos += ft_strlen(delimiters[j]);
			j++;
			while (j < cpt_delimiter && segment[pos] && segment[pos] == ' ')
				pos++;
		}
		*end_rdr = pos;
	}
	else
		*end_rdr = *begin_rdr;
	//ft_env_HEREDOC(minishell, stockage, cmd_index);
	ft_free_split(delimiters);
	minishell->command_line[cmd_index].redirect.heredoc = ft_format_stockage(stockage);
	return (1);
}
*/