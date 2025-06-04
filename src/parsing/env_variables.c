/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/04 17:31:49 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace_var(t_minishell *minishell, char *str)
{
	char *res;
	int	i;
	int	dollar;
	int	end_name;
	char *dollar_value;
	char *before;
	char	*after;

	if (!ft_search(str, '$'))
		return (str);
	i = 0;
	dollar = 0;
	res = NULL;
	before = NULL;
	after = NULL;
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
	{
		res = ft_substr(str, 1, ft_strlen(str) - 2);
		return (free(str), res);
	}
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		if (str[1] != '$')
		{
			while (str[i] && str[i + 1] != '$')
				i++;
			before = ft_substr(str, 1, i);
			res = ft_strjoin(res, ft_replace_var(minishell, before));
		}
		while (str[dollar] != '$')
			dollar++;
		end_name = dollar;
		while (str[end_name + 1] && str[end_name + 1] != ' ' && str[end_name + 1] != '\"')
			end_name++;
		dollar_value = ft_substr(str, dollar, end_name - dollar + 1);
		res = ft_strjoin(res, ft_replace_var(minishell, dollar_value));
		if (str[end_name + 1] && str[end_name + 1] != '\"')
		{
			
			after = ft_substr(str, end_name + 1, (ft_strlen(str) - end_name) - 2);
			res = ft_strjoin(res, ft_replace_var(minishell, after));
		}
		dollar_value = NULL;
		after = NULL;
		if (dollar_value)
			free(dollar_value);
		if (after)
			free(after);
		return (res);
	}
	if (str[dollar + 1] == '?')
		res = ft_itoa(minishell->rt_val);
	else
	{
		res = ft_strdup(ft_getenv(minishell->env, str + 1));
		if (!res)
			res = ft_strdup("");
	}
	return (free(str), res);
}

void	ft_env_HEREDOC(t_minishell *minishell, char **hd, int cmd_index)
{
	int	i;

	i = 0;
	while (hd[i])
	{
		if (ft_search(hd[i], '$') && 
		!ft_in_tab(minishell->command_line[cmd_index].redirect.hd_delimiters, hd[i]))
		{
			hd[i] = ft_replace_var(minishell, hd[i]);
			if (!hd[i])
				return ;
		}
		i++;
	}
}

void	ft_env_ARGS(t_minishell *minishell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_search(args[i], '$'))
		{
			args[i] = ft_replace_var(minishell, args[i]);
			if (!args[i])
				return ;
		}
		i++;
	}
}
