/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:57:23 by norabino          #+#    #+#             */
/*   Updated: 2025/06/10 16:41:07 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init(t_minishell *minishell, int nb_cmds)
{
	int	i;

	i = 0;
	minishell->command_line = malloc(nb_cmds * sizeof(t_command_line));
	if (!minishell->command_line)
		return (0);
	while (i < nb_cmds)
	{
		minishell->command_line[i].args = NULL;
		minishell->command_line[i].redirect.ri = NULL;
		minishell->command_line[i].redirect.hd_delimiters = NULL;
		minishell->command_line[i].redirect.ro = NULL;
		minishell->command_line[i].redirect.aro = NULL;
		minishell->command_line[i].redirect.heredoc = NULL;
		i++;
	}
	return (1);
}

void	ft_free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_free_tabtab(char ***args)
{
	int	i;
	int j;

	if (args == NULL)
		return ;
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			free (args[i][j]);
		free (args[i]);
	}
	free(args);
}

void free_command_lines(t_minishell *minishell)
{
	int	i;

	if (!minishell)
		return ;
	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (minishell->command_line[i].args)
			ft_free_split(minishell->command_line[i].args);
		if (minishell->command_line[i].redirect.ri)
			free(minishell->command_line[i].redirect.ri);
		if (minishell->command_line[i].redirect.heredoc)
			free(minishell->command_line[i].redirect.heredoc);
		if (minishell->command_line[i].redirect.ro)
			free(minishell->command_line[i].redirect.ro);
		if (minishell->command_line[i].redirect.aro)
			free(minishell->command_line[i].redirect.aro);
		i++;
	}
	if (minishell->command_line)
		free(minishell->command_line);
	if (minishell->line)
	free(minishell->line);
}