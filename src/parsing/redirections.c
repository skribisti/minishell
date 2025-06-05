/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:43:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/05 18:43:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"
//
//int	ft_which_redir(char *redir)
//{
//	if (redir[0] == '<' && redir[1] != '<')
//		return (1);
//	if (redir[0] == '>' && redir[1] != '>')
//		return (2);
//	if (redir[0] == '<' && redir[1] == '<')
//		return (3);
//	if (redir[0] == '>' && redir[1] == '>')
//		return (4);
//}
//
//int	ft_handle_redir(t_minishell *minishell, char *line, int cmd_index, int *i)
//{
//	int 	redir_size;
//	char 	*redir;
//	int		which_redir;
//	
//	redir_size = 0;
//	which_redir = ft_which_redir(&line[*i]);
//	while (line[*i] == ' ' || is_redir(&line[*i]))
//		i++;
//	while (line[*i + redir_size] && line[*i + redir_size] != ' ' )
//		redir_size++;
//	if (!line[*i + redir_size])
//		printf("minishell: syntax error near unexpected token 'newline'\n");
//	redir = ft_substr(&line, i, redir_size);
//	if (which_redir == 1)
//		minishell->command_line[cmd_index].redirect.ri = redir;
//	if (which_redir == 2)
//		minishell->command_line[cmd_index].redirect.ro = redir;
//	if (which_redir == 3)
//		minishell->command_line[cmd_index].redirect.aro = redir;
//	//if (which_redir == 4)
//		minishell->command_line[cmd_index].redirect.heredoc = redir;
//	return (1);
//}
//