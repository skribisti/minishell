/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:25:48 by norabino          #+#    #+#             */
/*   Updated: 2025/05/13 17:41:18 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	ft_get_indexes(char *segment, int *begin_rdr, int *end_rdr, int rdr_len)
{
	if (!rdr_len)
		return (0);
	*begin_rdr += rdr_len;
	while (segment[*begin_rdr] && segment[*begin_rdr] == ' ')
			(*begin_rdr)++;
	if (!segment[*begin_rdr])
		return (0);
	*end_rdr = *begin_rdr;
	while (segment[*end_rdr] && segment[*end_rdr] != ' ')
		(*end_rdr)++;
	return (1);
}

int	ft_get_rdrsize(char *segment, int redirection)
{
	if ((segment[redirection] == '<' && segment[redirection + 1] != '<')
		|| (segment[redirection] == '>' && segment[redirection + 1] != '>'))
		return (1);
	else if ((segment[redirection] == '<' && segment[redirection + 1] == '<')
		|| (segment[redirection] == '>' && segment[redirection + 1] == '>'))
		return (2);
	return (0);
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

void	ft_redirections(t_minishell *command, char *segment, int redirection, int begin_rdr, int cmd_index)
{
	int	end_rdr;

	end_rdr = 0;
	if (!ft_get_indexes(segment, &begin_rdr, &end_rdr, ft_get_rdrsize(segment, redirection)))
			return ;
	// ri <
	if (segment[redirection] == '<' && segment[redirection + 1] != '<')
		command->command_line[cmd_index].redirect.ri = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
	// heredoc <<
	else if (segment[redirection] == '<' && segment[redirection + 1] == '<')
		command->command_line[cmd_index].redirect.heredoc = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		//ft_parse_heredoc(command, cmd_index, segment, begin_rdr, end_rdr);
	// ro >
	else if (segment[redirection] == '>' && segment[redirection + 1] != '>')
		command->command_line[cmd_index].redirect.ro = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
	// aro >>
	else if (segment[redirection] == '>' && segment[redirection + 1] == '>')
		command->command_line[cmd_index].redirect.aro = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
	ft_set_spaces(segment, redirection, end_rdr - redirection);
}

void	ft_handle_redirections(t_minishell *command, char *segment, int cmd_index)
{
	int	begin_rdr;
	int redirection;

	while (1)
	{
		if (!ft_search(segment, '<') && !ft_search(segment, '>'))
			return ;
		redirection = 0;
		while (segment[redirection] != '<' && segment[redirection] != '>')
			redirection++;
		begin_rdr = redirection;
		
		if ((segment[redirection] == '<' && segment[redirection + 1] == '<') || 
            (segment[redirection] == '>' && segment[redirection + 1] == '>'))
            begin_rdr++;
		ft_redirections(command, segment, redirection, begin_rdr, cmd_index);
	}
}
