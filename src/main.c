/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/06/27 16:44:14 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

void	sig_handler(int signum)
{
	g_sig = signum;
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!is_executing(0))
			rl_redisplay();
	}
}

static void	handle_sigquit(void)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) == -1)
		return ;
	terminal.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == -1)
		return ;
	signal(SIGQUIT, &sig_handler);
}

void	ft_minishell(t_minishell minishell)
{
	while (1)
	{
		minishell.line = readline("$> ");
		if (!minishell.line)
			break ;
		if (*minishell.line)
		{
			if (g_sig == SIGINT)
			{
				minishell.rt_val = 130;
				g_sig = 0;
			}
			minishell.nb_cmd = ft_nbpipes(minishell.line) + 1;
			if (!verif_quotes(minishell.line)
				|| !ft_parse_line(&minishell))
				continue ;
			exec_cmd(&minishell);
			add_history(minishell.line);
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

	write(2, "Welcome to MINISHELL\n", 21);
	(void)argc;
	(void)argv;
	handle_sigquit();
	if (signal(SIGINT, &sig_handler) == SIG_ERR
		|| signal(SIGQUIT, NULL) == SIG_ERR)
		exit(1);
	minishell.rt_val = 0;
	minishell.env = cpy_env(env);
	upd_shlvl(&minishell);
	ft_minishell(minishell);
	return (0);
}
