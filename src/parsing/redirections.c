/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:43:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/16 18:43:08 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_which_redir(char *redir, int *i)
{
	if (redir[*i] == '<' && redir[*i  + 1] != '<')
		return ((*i)++, 1);
	if (redir[*i] == '>' && redir[*i + 1] != '>')
		return ((*i)++, 2);
	if (redir[*i] == '>' && redir[*i + 1] == '>')
		return ((*i) += 2, 3);
	if (redir[*i] == '<' && redir[*i + 1] == '<')
		return ((*i) += 2, 4);
	return (-1);
}


static int	set_redir(t_minishell *minishell, char *redir, int cmd_index, int which_redir)
{
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
		readline_heredoc(minishell, redir, cmd_index);
	return (1);
}

char *handle_redir(t_minishell *minishell, int cmd_idx, char *segment)
{
	char 	*redir;
	int		which_redir;
	int		start[2];
	int		i;

	i = 0;
	while (segment[i])
	{
		if (is_redir(&segment[i]))
		{
			start[0] = i;
			which_redir = ft_which_redir(segment, &i);
			skip_spaces(segment, &i);
			start[1] = i;
			redir = get_str(segment, &i);
			set_redir(minishell, redir, cmd_idx, which_redir);
			ft_set_spaces(segment, start[0], is_redir(&segment[start[0]]));
			ft_set_spaces(segment, start[1], ft_strlen(redir));
		}
		else
			i++;
	}
	return (segment);
}
