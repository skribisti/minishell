/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:57:23 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 18:23:03 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init(t_minishell *command, int nb_cmds)
{
	int	i;

	i = 0;
	command->command_line = malloc(nb_cmds * sizeof(t_command_line));
	command->redirects = malloc(nb_cmds * sizeof(t_rdr));
	if (!command->command_line || !command->redirects)
		return (0);
	while (i < nb_cmds)
	{
		command->command_line[i].cmd = NULL;
		command->command_line[i].args = NULL;
		command->command_line[i].splitted = NULL;
		command->redirects[i].ri = NULL;
		command->redirects[i].ro = NULL;
		command->redirects[i].aro = NULL;
		i++;
	}
	return (1);
}

void	ft_free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free (splitted[i]);
		i++;
	}
	free(splitted);
}

void free_command_lines(t_minishell *command)
{
	int	i;

	i = 0;
	while (i < command->nb_cmd)
	{
		if (command->command_line[i].args)
	    	free(command->command_line[i].args);
		if (command->command_line[i].cmd)
			free(command->command_line[i].cmd);
		if (command->command_line[i].splitted)
			ft_free_split(command->command_line[i].splitted);
		i++;
	}
	free(command->command_line);
}