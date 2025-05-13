/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/05/13 16:04:10 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_minishell()
{
	t_minishell	command;
	
	while (1)
	{
		command.line = readline("$> ");
		add_history(command.line);
		if (!command.line)
			break ;
		if (*command.line)
		{
			command.nb_cmd = ft_nbpipes(command.line) + 1;
			if (!verif_quotes(command.line))
			{
				printf("Error : Open quotes.\n");
				continue;
			}
			ft_parse_commandline(&command);
			ft_print_tokens(&command);
			//ft_parse_args_quotes(command.line);
			//ft_exec(); // ta fonction pour ton programme
			free_command_lines(&command);
			free(command.line);
		}
	}
	clear_history();	
}

int	main()
{
	ft_minishell();
	return (0);
}