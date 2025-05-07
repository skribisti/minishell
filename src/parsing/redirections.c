/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:25:48 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 19:27:40 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
int	ft_get_index(char *segment, int *end_rdr)
{
	while (segment[*end_rdr] && segment[*end_rdr] == ' ')
			(*end_rdr)++;
	if (!segment[*end_rdr])
		return (0);
	while (segment[*end_rdr] != ' ')
		(*end_rdr)++;
	return (1);
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

int	ft_handle_redirections(t_minishell *command, char *segment, int cmd_index)
{
	int	begin_rdr;
	int	end_rdr;

	while (1)
	{
		if (!ft_search(segment, '<') && !ft_search(segment, '>'))
			return (1);
		begin_rdr = 0;
		while (segment[begin_rdr] != '<' && segment[begin_rdr] != '>')
			begin_rdr++;
		begin_rdr++;
		end_rdr = begin_rdr + 1;
		// ri
		if (segment[begin_rdr] == '<')
		{
			if (!ft_get_index(segment, &end_rdr))
				return (0);
			command->redirects[cmd_index].ri = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		// ro
		else if (segment[begin_rdr] == '<' && segment[begin_rdr + 1] && segment[begin_rdr + 1] != '<')
		{
			if (!ft_get_index(segment, &end_rdr))
				return (0);
			command->redirects[cmd_index].ro = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		// aro
		else if (segment[begin_rdr] == '<' && segment[begin_rdr + 1] && segment[begin_rdr + 1] == '<')
		{
			if (!ft_get_index(segment, &end_rdr))
				return (0);
			command->redirects[cmd_index].aro = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		ft_set_spaces(segment, begin_rdr, end_rdr - begin_rdr);
	}
	
}