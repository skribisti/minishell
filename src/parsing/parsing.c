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
	int	i;
	int	j;

	i = 0;
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

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

char *get_str(char *seg, int *i)
{
	char	*res;
	int		size;
	char	quote;

	skip_spaces(seg, i);
	if (!seg[*i] || seg[*i] == '\0')
        return (NULL);
	size = 0;
	quote = 0;
	while (seg[size + (*i)])
	{
		if ((seg[size + (*i)] == '\'' || seg[size + (*i)] == '\"') && !quote)
			quote = seg[size + (*i)];
		else if (seg[size + (*i)] == quote)
			quote = 0;
		else if (seg[size + (*i)] == ' ' && !quote)
			break;
		size++;
	}
	res = ft_substr(seg, *i, size);
	(*i) += size;
	return (res);
}

void	ft_malloc_args(t_minishell *minishell, char *segment)
{
	char	*tmp;
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	tmp = get_str(segment, &i);
	while (tmp)
	{
		cpt++;
		tmp = get_str(segment, &i);
	}
	minishell->command_line->args = malloc(sizeof(char *) * (cpt + 1));
}

int ft_parse_segment(t_minishell *minishell, int cmd_idx, char *segment)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_malloc_args(minishell, segment);
	if (!minishell->command_line->args)
		return (-1);
	while (segment[i])
	{
		handle_redir(minishell, cmd_idx, segment, &i);
		replace_all_var(minishell, segment);
		minishell->command_line[cmd_idx].args[j] = get_str(segment, &i);
		j++;
	}
	minishell->command_line[cmd_idx].args[j] = NULL;
	minishell->command_line[cmd_idx].args = remove_quotes(minishell->command_line[cmd_idx].args);
	return (1);
}

int	is_char_invalid(char c)
{
	if (c == ' ' || c == '|' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	handle_parse_errors(int error)
{
	if (error == -1)
		printf("minishell: syntax error near unexpected token '|'\n");
	else if (error == 0)
		printf("minishell: syntax error near unexpected token 'newline'\n");
}

int	is_line_valid(char *str, int nb_cmd)
{
	int	i;

	i = 0;
	skip_spaces(str, &i);
	if (nb_cmd >= 2 && str[i] == '|')
		return (-1);
	while (str[i])
	{
		if (is_redir(&str[i]))
		{
			i += is_redir(&str[i]);
			skip_spaces(str, &i);
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int ft_parse_line(t_minishell *minishell)
{
	int cmd_idx;
	int pipe_start;
	int pipe_end;
	char *cmd_segment;

	cmd_idx = 0;
	pipe_start = 0;
	pipe_end = 0;
	ft_init(minishell, minishell->nb_cmd);
	if (is_line_valid(minishell->line, minishell->nb_cmd) != 1)
		return (handle_parse_errors(is_line_valid(minishell->line, minishell->nb_cmd)), 0);
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

