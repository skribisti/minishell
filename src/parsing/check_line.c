/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:54:01 by norabino          #+#    #+#             */
/*   Updated: 2025/06/19 19:20:46 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error(char c)
{
	if (!c)
	{
		write(2, "minishell: syntax error near ", 29);
		write(2, "unexpected token 'newline'\n", 27);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
}

int	check_redir(char *str, int i)
{
	i += is_redir(&str[i]);
	skip_chars(str, &i, ' ');
	if (!str[i] || str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (print_error(str[i]), 0);
	return (1);
}

int	check_pipes(char *str, int i)
{
	int	j;

	j = i - 1;
	while (j >= 0 && str[j] == ' ')
		j--;
	if (j == -1)
		return (print_error('|'), 0);
	i++;
	skip_chars(str, &i, ' ');
	if (!str[i])
		return (print_error('|'), 0);
	return (1);
}

int	is_line_valid(char *str, int nb_cmd)
{
	int	i;

	i = 0;
	skip_chars(str, &i, ' ');
	if (nb_cmd >= 2 && str[i] == '|')
		return (print_error(str[i]), 0);
	while (str[i])
	{
		if (is_redir(&str[i]) && !check_redir(str, i))
			return (0);
		if (str[i] == '|' && !check_pipes(str, i))
			return (0);
		i++;
	}
	return (1);
}
