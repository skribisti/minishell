/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/04 15:32:07 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace_var(t_minishell *minishell, char *str)
{
	char *res;
	int	dollar;
	int	end_name;
	char *sub_var;

	dollar = 0;
	while (str[dollar] && str[dollar] != '$')
		dollar++;
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
	{
		res = ft_substr(str, 1, ft_strlen(str) - 2);
		return (free(str), res);
	}
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		end_name = dollar;
		while (str[end_name] && str[end_name] != ' ' && str[end_name] != '\"')
			end_name++;
		end_name--;
		sub_var = ft_substr(str, dollar, dollar - end_name);
		printf("subvar = %s", sub_var);
		res = ft_replace_var(minishell, sub_var);
		return (free(sub_var), res);
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
