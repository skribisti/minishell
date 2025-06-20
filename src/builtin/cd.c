/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:09:32 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/13 16:16:48 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dirrectory(char *path)
{
	struct stat	info;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &info) == 0 && S_ISDIR(info.st_mode))
			return (1);
	}
	return (0);
}

static void	update_pwd_env(t_minishell *minishell)
{
	char	cwd[200];
	char	*old_pwd;

	old_pwd = ft_getenv(minishell->env, "PWD");
	if (old_pwd)
		minishell->env = set_var_env(minishell->env, "OLDPWD", old_pwd);
	if (getcwd(cwd, 200))
		minishell->env = set_var_env(minishell->env, "PWD", cwd);
}

int	ft_cd(char **argv, t_minishell *minishell)
{
	char	*path;

	if (!argv[1])
	{
		path = ft_getenv(minishell->env, "HOME");
		if (!path)
			return (write(2, "cd: HOME not set\n", 17), 0);
	}
	else
		path = argv[1];
	if (access(path, F_OK) != 0)
		return (write(2, "cd: No such file or directory\n", 30), 1);
	if (!is_dirrectory(path))
		return (write(2, "cd: Not a directory\n", 20), 1);
	chdir(path);
	update_pwd_env(minishell);
	return (0);
}
