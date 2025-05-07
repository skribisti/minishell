/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:42 by norabino          #+#    #+#             */
/*   Updated: 2025/05/06 14:48:18 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef	struct s_command_line
{
	char *cmd;
	char *args;
	char **splitted;
}	t_command_line;

typedef struct s_minishell
{
	char	*line;
	int		nb_cmd;
	t_command_line	*command_line;
}	t_minishell;

char	**ft_split(char const *str, char c);
