/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:00 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 15:29:16 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	verif_quotes(char *str)
{
	int	simple_q;
	int	double_q;
	int	i;

	simple_q = 0;
	double_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			double_q++;
		else if (str[i] == 39)
			simple_q++;
		i++;	
	}
	if (double_q % 2 != 0 || simple_q % 2 != 0)
		return (0);
	return (1);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_handle_meta_chars(char *prompt, int begin)
{
	int		i;
	int		size;
	char	*string;
	
	i = begin;
	while (prompt[i] != 34 && prompt[i] != 39)
		i++;
	size = i - begin;
	string = ft_substr(prompt, begin, size);
	if (!string)
		return (NULL);
	return (string);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	size_t	i;

	if (!c)
		return (exit(1), NULL);
	i = 0;
	if (s1)
		res = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	else
		res = (char *)malloc(2 * sizeof(char));
	if (!res)
		return (exit(1), NULL);
	if (s1)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	res[i] = c;
	res[i + 1] = '\0';
	if (s1)
		free(s1);
	return (res);
}

int	ft_count_seps(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			nb++;
		i++;
	}
	return (nb);
}

int	ft_init(t_minishell *command, int nb_cmds)
{
	int	i;

	i = 0;
	command->command_line = malloc(nb_cmds * sizeof(t_command_line));
	if (!command->command_line)
		return (0);
	while (i < nb_cmds)
	{
		command->command_line[i].cmd = NULL;
		command->command_line[i].args = NULL;
		command->command_line[i].splitted = NULL;
		i++;
	}
	return (1);
}

int	ft_parse_args_quotes(char *line)
{
	int beg;

	// 34 = double quotes
	// 39 = single quote
	beg = 0;
	while (line[beg] && (line[beg] != '"' && line[beg] != 39))
		beg++;
	if (line[beg] != 34 && line[beg] != 39)
		return (printf("No quotes"), 1);
	printf("%s", ft_handle_meta_chars(line, beg + 1));
	return (0);
}


char	*ft_strdup(char *str)
{
	char	*tab;
	int		i;

	tab = (char *)malloc(ft_strlen(str) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

int	ft_ind_firstspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	ft_nbpipes(char *line)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (line[i])
	{
		if (line[i] == '|')
			cpt++;
		i++;
	}
	return (cpt);
}

int	ft_nextpipe(char *line, int last_pipe)
{
	while (line[last_pipe] && line[last_pipe] != '|')
		last_pipe++;
	return (last_pipe);
}

int	ft_print_tokens(t_minishell *command)
{
	int	i = 0;
	int	j;

	while (i < command->nb_cmd)
	{
		printf("Command %d:\n", i + 1);
		printf("CMD = %s\n", command->command_line[i].cmd);
		printf("ARGS = %s\n\n", command->command_line[i].args);
		
		if (command->command_line[i].splitted)
		{
			printf("Splitted arguments:\n");
			j = 0;
			while (command->command_line[i].splitted[j])
			{
				printf("  [%d] %s\n", j, command->command_line[i].splitted[j]);
				j++;
			}
		}
		printf("\n\n");
		i++;
	}
	return (0);
}

void	ft_free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free (splitted[i]);
		i++;
	}
	free(splitted);
}

void free_tokens(t_minishell *command)
{
	int	i;

	i = 0;
	while (i < command->nb_cmd)
	{
		if (command->command_line[i].args)
	    	free(command->command_line[i].args);
		if (command->command_line[i].cmd)
			free(command->command_line[i].cmd);
		if (command->command_line[i].splitted)
			ft_free_split(command->command_line[i].splitted);
		i++;
	}
	free(command->command_line);
}

int ft_parse_commandsegment(t_minishell *command, int cmd_index, char *segment)
{
    int space_index;
    int start = 0;
    
    while (segment[start] && segment[start] == ' ')
        start++;
    space_index = start;
    while (segment[space_index] && segment[space_index] != ' ')
        space_index++;
        
    if (segment[space_index] == '\0')
    {
        command->command_line[cmd_index].cmd = ft_strdup(segment + start);
        command->command_line[cmd_index].args = ft_strdup(segment);
    }
    else
    {
        command->command_line[cmd_index].cmd = ft_strdup(
            ft_substr(segment, start, space_index - start));
        command->command_line[cmd_index].args = ft_strdup(segment);
        command->command_line[cmd_index].splitted = ft_split(segment, ' ');
    }
    return (0);
}

int ft_parse_commandline(t_minishell *command)
{
    int i = 0;
    int pipe_start = 0;
    int pipe_end = 0;
    char *cmd_segment;

    command->nb_cmd = ft_nbpipes(command->line) + 1;
    ft_init(command, command->nb_cmd);
    while (i < command->nb_cmd)
    {
        pipe_end = ft_nextpipe(command->line, pipe_start);
        cmd_segment = ft_substr(command->line, pipe_start, (pipe_end - pipe_start));
        ft_parse_commandsegment(command, i, cmd_segment);
        pipe_start = pipe_end + 1;
        i++;
        free(cmd_segment);
    }
    
    return (0);
}

int	main()
{
	t_minishell	command;
	
	while (1)
	{
		command.line = readline("$> ");
		if (!command.line)
			break ;
		if (*command.line)
		{
			command.nb_cmd = ft_nbpipes(command.line) + 1;
			if (!verif_quotes(command.line))
			{
				printf("Error : Open quotes.\n");
				continue;
			}
			ft_parse_commandline(&command);
			ft_print_tokens(&command);
			//ft_parse_args_quotes(command.line);
			//ft_exec(); // ta fonction pour ton programme
		}
		free_tokens(&command);
		free(command.line);
	}
	return (0);
}
