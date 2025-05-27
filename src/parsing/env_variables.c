/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:41:31 by norabino          #+#    #+#             */
/*   Updated: 2025/05/27 15:19:21 by norabino         ###   ########.fr       */
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
		*segment = new;
		diff = var_size - var_$_size;
		i = ft_strlen(*segment);
		while (i >= 0 && i >= dollar + var_$_size)
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
		(c == '_') || (c == '?'))
		return (1);
	return (0);
}

/*void	ft_handle_env_variables(t_minishell *minishell, char **segment, int cmd_index)
{
	int dollar_ind;
	int	end;
	char *env_value;
	char	*var = NULL;;
	char *sub;
	int	var_$_size;

	if (!segment || !*segment || !**segment)
		return ;
	while (*segment && ft_search(*segment, '$'))
	{
		dollar_ind = 0;
		while ((*segment)[dollar_ind] && (*segment)[dollar_ind] != '$')
			dollar_ind++;
		if (!(*segment)[dollar_ind] || !(*segment)[dollar_ind + 1])
			break;
		end = dollar_ind + 1;
		if (!ft_is_valid((*segment)[end]))
		{
			//printf("not valid name");
			dollar_ind++;
			continue;
		}
		while ((*segment)[end] && ft_is_valid((*segment)[end]))
			end++;
		var_$_size = end - dollar_ind;
		sub = ft_substr(*segment, dollar_ind + 1, var_$_size - 1);
		if (!sub)
			return ;

		(void)cmd_index; // TO BYPASS COMPILATION WARNINGS
		//if (ft_in_tab(minishell->command_line[cmd_index].redirect.hd_delimiters, sub))
		//{
			//free(sub);
			//(*segment)[dollar_ind] = ' ';
			//continue;
		//}
		if (var)
		{
			free(var);
			var = NULL;
		}
		if (!ft_strcmp(sub, "?"))
		{
			var = ft_itoa(minishell->rt_val);
			free(sub);
			if (!var)
				return ;
		}
		else
		{
			env_value = ft_getenv(minishell->env, sub);
			free(sub);
			if (!env_value)
			{
				var = ft_strdup("");
				if (!var)
					return ;
			}
			else
			{
				var = ft_strdup(env_value);
				if (!var)
					return ;
			}
		}
		if (var)
			ft_replace_var(segment, var, dollar_ind, var_$_size);
		free(var);
		if (!*segment)
			return ;
	}
	return ;
}*/

void	ft_handle_env_variables(t_minishell *minishell, char **segment, int cmd_index)
{
    int dollar_ind;
    int	end;
    char *env_value;
    char	*var;
    char *sub;
    int	var_$_size;

    if (!segment || !*segment || !**segment)
        return ;
    while (ft_search(*segment, '$'))
    {
        dollar_ind = 0;
        while ((*segment)[dollar_ind] && (*segment)[dollar_ind] != '$')
            dollar_ind++;
		if (!(*segment)[dollar_ind] || !(*segment)[dollar_ind + 1])
            break;
        end = dollar_ind + 1;
        // CHANGE 2: Remove debug printf which could cause issues
        // Just skip invalid names silently
        if (!ft_is_valid((*segment)[end]))
        {
            dollar_ind++;
            continue;
        }
        while ((*segment)[end] && ft_is_valid((*segment)[end]))
            end++;
        var_$_size = end - dollar_ind;
        sub = ft_substr(*segment, dollar_ind + 1, var_$_size - 1);
        if (!sub)
            return ;

        (void)cmd_index;
        /*if (ft_in_tab(minishell->command_line[cmd_index].redirect.hd_delimiters, sub))
        {
            free(sub);
            (*segment)[dollar_ind] = ' ';
            continue;
        }*/
        if (!ft_strcmp(sub, "?"))
        {
            var = ft_itoa(minishell->rt_val);
            free(sub);
			sub = NULL;
            if (!var)
                return ;
        }
        else
        {
            env_value = ft_getenv(minishell->env, sub);
            free(sub);
			sub = NULL;
            // CHANGE 3: Simplify this logic to avoid potential memory issues
            // Replace these nested if-else blocks with simpler code
            if (!env_value)
            {
                var = ft_strdup("");
                if (!var)
                    return ;
            }
            else
            {
                var = ft_strdup(env_value);
                if (!var)
                    return ;
            }
        }
		if (var)
		{
        	ft_replace_var(segment, var, dollar_ind, var_$_size);
			free(var);
		}
        // CHANGE 5: Ensure we break out correctly if *segment is NULL
        if (!*segment)
            return ;
    }
    return ;
}


// PROMPT copilot for heredoc delimiters
/*i want you to help me fill my function (env_variables.c, line 104, where i put //HERE), here is the case when my '$' + 'var name' follow an heredoc redirection. i have to reimplement the exact same behavior than Bash, that is to say i have to replace the variables names by their values in the env ONLY if they arent an heredoc delimiters. i put you the condition line 102, if we enter in the if we know that sub (name of env var without $) is an heredoc delimiter, all you have to do now is implement the rest. by "the rest" i mean making sure that my $ and what is just next, not be considered as an variable name*/