/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:43:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/11 16:53:45 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_which_redir(char *redir, int *i)
{
	if (redir[*i] == '<' && redir[*i  + 1] != '<')
		return ((*i)++, 1);
	if (redir[*i] == '>' && redir[*i + 1] != '>')
		return ((*i)++, 2);
	if (redir[*i] == '<' && redir[*i + 1] == '<')
		return ((*i) += 2, 3);
	if (redir[*i] == '>' && redir[*i + 1] == '>')
		return ((*i) += 2, 4);
	return (-1);
}

void	add_heredoc(t_minishell *minishell, char *str, int cmd_index)
{
	static int	i = 1;

	minishell->command_line[cmd_index].redirect.hd_delimiters = ft_realloc(minishell->command_line[cmd_index].redirect.hd_delimiters, sizeof(char *) * i, sizeof(char *) * i + 1);
	minishell->command_line[cmd_index].redirect.hd_delimiters[i - 1] = str;
	minishell->command_line[cmd_index].redirect.hd_delimiters[i] = NULL;
	i++;
}

int	set_redir(t_minishell *minishell, char **segment, int cmd_index, int *i)
{
	char 	*redir;
	int		which_redir;
	int		tmp;
	
	tmp = *i;
	which_redir = ft_which_redir(*segment, i);
	redir = get_str(*segment, i);
	if (which_redir == 1)
		free(minishell->command_line[cmd_index].redirect.ri);
	if (which_redir == 1)
		minishell->command_line[cmd_index].redirect.ri = redir;
	if (which_redir == 2)
		free(minishell->command_line[cmd_index].redirect.ro);
	if (which_redir == 2)
		minishell->command_line[cmd_index].redirect.ro = redir;
	if (which_redir == 3)
		free(minishell->command_line[cmd_index].redirect.aro);
	if (which_redir == 3)
		minishell->command_line[cmd_index].redirect.aro = redir;
	if (which_redir == 4)
		add_heredoc(minishell, redir, cmd_index);
	ft_set_spaces(*segment, tmp, ft_strlen(*segment) - tmp);
	return (1);
}

char	*handle_redir(t_minishell *minishell, int cmd_idx, char *segment, int *i)
{
	skip_spaces(segment, i);
	if (is_redir(&segment[*i]) 
		&& set_redir(minishell, &segment, cmd_idx, i))
		return (NULL);
	return (segment);
}
