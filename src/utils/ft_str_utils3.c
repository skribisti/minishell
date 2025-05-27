/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:50 by norabino          #+#    #+#             */
/*   Updated: 2025/05/21 18:59:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_nextpipe(char *line, int last_pipe)
{
	while (line[last_pipe] && line[last_pipe] != '|')
		last_pipe++;
	return (last_pipe);
}

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (0);
	i = -1;
	while (++i < len1)
		res[i] = s1[i];
	i--;
	while (++i < len1 + len2)
		res[i] = s2[i - len1];
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == 0)
			return (0);
		i++;
	}
	return (&s[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}



int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i])
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}



void	ft_set_spaces(char *segment, int begin, int length)
{
    int	i;

    i = 0;
    while (i < length && segment[begin + i])
    {
        segment[begin + i] = ' ';
        i++;
    }
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_cpt_heredoc(char *segment)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (segment[i])
	{
		if (segment[i] == '<' && segment[i + 1] == '<')
		{
			cpt++;
			i += 2;
		}
		else
			i++;
	}
	return (cpt);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;
	int		sign;

	num = n;
	len = (n <= 0);
	sign = (n < 0);
	if (sign)
		num = -num;
	while (n && ++len)
		n /= 10;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

int	ft_in_tab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], str))
			return (1);
		i++;
	}
	return (0);
}