/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/20 17:16:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_var(char c)
{
	if (!(('A' <= c && c <= 'Z')
			|| ('a' <= c && c <= 'z')
			|| ('0' <= c && c <= '9')
			|| c == '_'))
		return (0);
	return (1);
}

char	*ft_replace_var(t_minishell *minishell, char *str, int *start)
{
	int		j;
	char	*var;
	char	*res;

	j = 0;
	(*start)++;
	var = NULL;
	if (str[(*start)] != '$' && str[(*start)] == '?')
		var = ft_itoa(minishell->rt_val);
	else if (str[(*start)] != '$')
	{
		while (ft_is_var(str[(*start) + j]))
			j++;
		res = ft_substr(str, (*start), j);
		var = ft_getenv(minishell->env, res);
		free(res);
	}
	if (!var)
		res = ft_strndup(str, (*start));
	else
		res = ft_strndup(str, (*start) - 1);
	res = ft_join_free(ft_join_free(res, var, 0), &str[(*start) + j], 0);
	(*start) += ft_strlen(var) + 1;
	return (res);
}

char	*replace_all_var(t_minishell *minishell, char *line)
{
	char	*tmp;
	int		tab[2];

	tab[0] = 0;
	tab[1] = 0;
	tmp = line;
	while (line && line[tab[0]])
	{
		if (line[tab[0]] == '\'' && !tab[1])
			tab[1] = line[tab[0]];
		else if (line[tab[0]] == '\'' && tab[1])
			tab[1] = 0;
		if (line[tab[0]] == '<' && line[tab[0] + 1] == '<' && !tab[1])
		{
			tab[0] += 2;
			free(get_str(line, &tab[0]));
		}
		else if (!tab[1] && line[tab[0]] == '$')
			line = ft_replace_var(minishell, line, &tab[0]);
		else
			tab[0]++;
	}
	if (tmp == line)
		return (ft_strdup(line));
	return (line);
}
