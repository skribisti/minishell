/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:09:34 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/30 15:49:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	no_newline(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!argv[1])
		return (printf("\n"), 0);
	while (argv[i] && no_newline(argv[i]))
	{
		n = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
