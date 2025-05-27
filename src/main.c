/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/05/27 16:05:07 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_minishell(t_minishell minishell)
{
	while (1)
	{
		//ft_update_SHLVL(&minishell);
		minishell.line = readline("$> ");
		add_history(minishell.line);
		if (!minishell.line)
			break ;
		if (*minishell.line)
		{
			minishell.nb_cmd = ft_nbpipes(minishell.line) + 1;
			if (!verif_quotes(minishell.line))
			{
				printf("Error : Open quotes.\n");
				continue;
			}
			ft_parse_commandline(&minishell);
			//ft_print_tokens(&minishell);
			exec_cmd(&minishell);
			free_command_lines(&minishell);
		}
	}
	clear_history();	
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell.env = cpy_env(env);
	ft_minishell(minishell);
	return (0);
}