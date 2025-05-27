/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:55:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/21 18:37:58 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_SHLVL(t_minishell *minishell)
{
	char *new_value = "1";
	char *entry = ft_strjoin("SHLVL=", new_value);
	if (entry)
	{
		int idx = get_env_index(minishell->env, "SHLVL");
		free(minishell->env[idx]);
		minishell->env[idx] = entry;
	}
}

char	*ft_getenv(char **env, char *var)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			if (env[i][j] != var[j])
				break ;
			j++;
		}
		if (env[i][j] == '=' && var[j] == '\0')
			return (&env[i][j + 1]);
	}
	return (NULL);
}

int	get_env_index(char **env, char *name)
{
	int		i;
	int		n_len;

	i = -1;
	n_len = ft_strlen(name);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, n_len))
			return (i);
	}
	return (-1);
}