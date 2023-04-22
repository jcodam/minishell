/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 17:28:27 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/22 14:54:46 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

static char	*get_home(char **env)
{
	int		i;
	char	*home;

	home = NULL;
	i = ft_env_index(env, "HOME");
	if (i == -1)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		g_exit_code = 1;
		return (0);
	}
	home = ft_env_content(env[i]);
	return (home);
}

int	ft_change_dir(char *path, char **env)
{
	int		i;
	char	*home;

	home = NULL;
	if (!path)
	{
		home = get_home(env);
		if (!home)
			return (0);
		path = home;
	}
	i = chdir(path);
	if (i == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(":No such file or directory\n", 1);
		g_exit_code = 1;
	}
	if (home)
		free(home);
	return (0);
}
