/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/05 19:27:52 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_join_free(char *s1, char *s2)
{
	char *res;
	
	res = ft_strjoin(s1, s2);
	if (s2)
		free(s1);
	return (res);
}

int	ft_is_var(char c)
{
	if (!(('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9')
		|| c == '_'))
		return (0);
	return (1);
}

char	*ft_replace_var(t_minishell *minishell, char *str, int start)
{
	int		j;
	char	*var;
	char	*res;

	j = 0;
	start++;
	while (ft_is_var(str[start + j]))
		j++;
	res = ft_substr(str, start, j);
	var = ft_getenv(minishell->env, res);
	free(res);
	res = ft_strndup(str, start - 1);
	res = ft_join_free(res, var);
	res = ft_join_free(res, &str[start + j]);
	return (res);
}
