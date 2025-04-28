/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:00 by norabino          #+#    #+#             */
/*   Updated: 2025/04/28 15:37:19 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
	while (i < len && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_handle_meta_chars(char *prompt, int begin, int quote)
{
	int		i;
	int		size;
	char	*string;
	
	i = begin;
	while (prompt[i] != quote)
		i++;
	size = i - begin;
	string = ft_substr(prompt, begin, size);
	if (!string)
		return (NULL);
	return (string);
}

#include <stdio.h>
int	main()
{
	char *str = "alloou\"isaluta\"llez";
	char *res;
	int beg;
	int quotes = 34;
	// 34 = double quotes
	// 39 = single quote

	beg = 0;
	while (str[beg] && str[beg] != quotes)
		beg++;
	if (str[beg] != quotes)
		return (printf("no quotes"), 0);
	res = ft_handle_meta_chars(str, beg + 1, quotes);
	printf("%s\n", str);
	printf("%s", res);
	return (1);
}
