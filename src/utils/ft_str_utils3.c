/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:50 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 15:56:05 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_nextpipe(char *line, int last_pipe)
{
	while (line[last_pipe] && line[last_pipe] != '|')
		last_pipe++;
	return (last_pipe);
}