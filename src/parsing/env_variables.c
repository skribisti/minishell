/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:41:31 by norabino          #+#    #+#             */
/*   Updated: 2025/05/21 17:20:03 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_replace_var(char **segment, char *var, int dollar, int var_$_size)
{
	int	i;
	int	diff;
	int	var_size;
	char	*new;

	if (!*segment || !var)
		return ;
	var_size = ft_strlen(var);
	if (var_size > var_$_size)
	{
		new = ft_realloc(*segment, ft_strlen(*segment) + 1, 
		ft_strlen(*segment) + (ft_strlen(var) - var_$_size) + 1);
		if (!new)
		{
			free(*segment);
			*segment = NULL;
			return;
		}
		*segment = ft_strdup(new);
		diff = var_size - var_$_size;
		i = ft_strlen(*segment);
		while (i >= dollar + var_$_size && i >= 0)
		{
			(*segment)[i + diff] = (*segment)[i];
			i--;
		}
	}
	else if (var_size < var_$_size)
	{
		diff = var_$_size - var_size;
		i = dollar + var_size;
		while ((*segment)[i + diff])
		{
			(*segment)[i] = (*segment)[i + diff];
			i++;
		}
		(*segment)[i] = 0;
	}
	i = 0;
	while (var[i])
	{
		(*segment)[dollar + i] = var[i];
		i++;
	}
}

int	ft_is_valid(char c)
{
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		(c == '_'))
		return (1);
	return (0);
}

void	ft_handle_env_variables(t_minishell *minishell, char **segment)
{
	int dollar_ind;
	int	end;
	char *var;
	char *sub;
	int	var_$_size;

	if (!segment || !*segment || !**segment)
		return ;
	while (ft_search(*segment, '$'))
	{
		dollar_ind = 0;
		while ((*segment)[dollar_ind] && (*segment)[dollar_ind] != '$')
			dollar_ind++;
		if ((*segment)[dollar_ind] == '$' && !(*segment)[dollar_ind + 1])
			break;
		end = dollar_ind + 1;
		if (!ft_is_valid((*segment)[end]))
		{
			(*segment)[dollar_ind] = ' ';
			continue;
		}
		while ((*segment)[end] && ft_is_valid((*segment)[end]))
			end++;
		var_$_size = end - dollar_ind;
		sub = ft_substr(*segment, dollar_ind + 1, var_$_size - 1);
		if (!sub)
			return ;
		var = ft_getenv(minishell->env, sub);
		free(sub);
		if (!var)
		{
			var = ft_strdup("");
			if (!var)
				return ;
		}
		ft_replace_var(segment, var, dollar_ind, var_$_size);
		if (!*segment)
			return ;
		if (!var || !*var)
			free(var);
	}
	return ;
}
