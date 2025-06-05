/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:34:29 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/05 17:44:33 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



char *handle_quotes(char *str, int *i)
{
	char	*quote;
	char	*in;
	int		size;

	quote = str[*i];
	size = 0;
	while (str[*++i] != quote)
		size++;
	in = ft_substr(str, *i, size);
	
}