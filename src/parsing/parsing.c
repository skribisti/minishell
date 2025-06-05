/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:00 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/05 1750:02 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_tokens(t_minishell *minishell)
{
	int	i = 0;
	int	j;

	while (i < minishell->nb_cmd)
	{
		printf("Command %d:\n", i + 1);
		if (minishell->command_line[i].args)
		{
			printf(" Arguments :\n");
			j = 0;
			while (minishell->command_line[i].args[j])
			{
				printf("  [%d] %s\n", j, minishell->command_line[i].args[j]);
				j++;
			}
		}
		if (minishell->command_line[i].redirect.ri || minishell->command_line[i].redirect.heredoc || minishell->command_line[i].redirect.ro || minishell->command_line[i].redirect.aro)
			printf("\n Redirections :\n");
		if (minishell->command_line[i].redirect.ri)
			printf("  RI = %s\n", minishell->command_line[i].redirect.ri);
		if (minishell->command_line[i].redirect.heredoc)
			printf("  HEREDOC =\n%s\n", minishell->command_line[i].redirect.heredoc);
		if (minishell->command_line[i].redirect.ro)
			printf("  RO = %s\n", minishell->command_line[i].redirect.ro);
		if (minishell->command_line[i].redirect.aro)
			printf("  ARO = %s\n", minishell->command_line[i].redirect.aro);
		printf("\n\n");
		i++;
	}

	return (0);
}

/*int ft_parse_segment(t_minishell *minishell, int cmd_index, char *segment)
{
	int space_index;
	int start = 0;
	
	if (handle_redir(minishell, segment, cmd_index) == -1)
		return (0);
	while (segment[start] && segment[start] == ' ')
		start++;
	space_index = start;
	while (segment[space_index] && segment[space_index] != ' ')
		space_index++;
	minishell->command_line[cmd_index].args = ft_split_line(segment, ' ');
	ft_env_ARGS(minishell, minishell->command_line[cmd_index].args);
	return (1);
}*/

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

char *get_arg(char *seg, int *i)
{
	char	*res;
	int		size;
	char	quote;

	skip_spaces(seg, i);
	size = 0;
	quote = 0;
	while (seg[size + (*i)])
	{
		if ((seg[size + (*i)] == '\'' || seg[size + (*i)] == '\"') && !quote)
			quote = seg[size + (*i)];
		else if (seg[size + (*i) == quote])
			quote = 0;
		else if (seg[size + (*i)] == ' ' && !quote)
			break;
		size++;
	}
	res = ft_substr(seg, *i, size);
	(*i) += size;
	return (res);
}

int ft_parse_segment(t_minishell *minishell, int cmd_idx, char *segment)
{
	int	i;
	//int	j;

	(void)cmd_idx;
	i = 0;
	//j = 0;
	skip_spaces(segment, &i);
	/*if (is_redir(segment, &i))
	{
		if (handle_redir(minishell, segment, cmd_idx, &i) == -1)
			return (0);
	}*/
	ft_print_string(ft_replace_var(minishell, get_arg(segment, &i), 1));
	//minishell->command_line[cmd_idx].args[j] = ft_replace_var(minishell, get_arg(segment, &i), 0);
	return (1);
}

int ft_parse_line(t_minishell *minishell)
{
	int cmd_idx = 0;
	int pipe_start = 0;
	int pipe_end = 0;
	char *cmd_segment;

	ft_init(minishell, minishell->nb_cmd);
	while (cmd_idx < minishell->nb_cmd)
	{
		pipe_end = ft_nextpipe(minishell->line, pipe_start);
		cmd_segment = ft_substr(minishell->line, pipe_start, (pipe_end - pipe_start));
		if (!ft_parse_segment(minishell, cmd_idx, cmd_segment))
			return (0);
		pipe_start = pipe_end + 1;
		cmd_idx++;
		free(cmd_segment);
	}
	return (1);
}

