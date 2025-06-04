/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/06/04 17:28:33 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_minishell(t_minishell minishell)
{
	while (1)
	{
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
			if (!ft_parse_line(&minishell))
				continue;
			//ft_print_tokens(&minishell);
			exec_cmd(&minishell);
			free_command_lines(&minishell);
		}
	}
	free(minishell.line);
	ft_free_split(minishell.env);
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	printf("Welcome to MINISHELL\n");
	(void)argc;
	(void)argv;
	minishell.env = cpy_env(env);
	upd_shlvl(&minishell);
	ft_minishell(minishell);
	return (0);
}
