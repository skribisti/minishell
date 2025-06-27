/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:29:36 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/27 17:26:50 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_heredoc(t_minishell *minishell, int pipes[2], int ixd)
{
	if (minishell->command_line[ixd].redirect.heredoc)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
	}
	return ;
}

int	try_to_open(char *name)
{
	int	fd;

	fd = 0;
	if (name)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	redirect_output(t_minishell *minishell, int idx)
{
	int	fd;

	fd = try_to_open(minishell->command_line[idx].redirect.aro);
	if (fd == -1)
	{
		perror(minishell->command_line[idx].redirect.aro);
		minishell->rt_val = 1;
		return (-1);
	}
	fd = try_to_open(minishell->command_line[idx].redirect.ro);
	if (fd == -1)
	{
		perror(minishell->command_line[idx].redirect.ro);
		minishell->rt_val = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redirect_input(t_minishell *minishell, int idx)
{
	int	fd;

	fd = open(minishell->command_line[idx].redirect.ri, O_RDONLY);
	if (fd == -1)
	{
		perror(minishell->command_line[idx].redirect.ri);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}
