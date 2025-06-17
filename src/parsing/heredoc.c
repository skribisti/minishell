/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:34 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/17 17:45:20 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	readline_heredoc(t_minishell *minishell, char *delimiter, int cmd_idx)
{
	char	*input;

	free(minishell->command_line[cmd_idx].redirect.ri);
	minishell->command_line[cmd_idx].redirect.ri = NULL;
	free(minishell->command_line[cmd_idx].redirect.heredoc);
	minishell->command_line[cmd_idx].redirect.heredoc = ft_strdup("");
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			return (write(2, "minishell: warning: here-document end-of-file\n", 46), 0);
		if (!ft_strcmp(input, delimiter))
			return (free(input), 0);
		minishell->command_line[cmd_idx].redirect.heredoc = ft_join_free(ft_join_free(minishell->command_line[cmd_idx].redirect.heredoc, input), "\n");
		free(input);
	}
	return (1);
}
