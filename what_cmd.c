/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   what_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:03:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/31 16:19:24 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	look_for_cmd(char **cmd, char *line, int *found, char *commend)
{
	*cmd = ft_strnstr(line, commend, 9);
	if (!*cmd)
		return (0);
	*found += 1;
	return (1);
}

int	what_cmd(char *line, char ***env)
{
	int		found;
	char	*cmd;

	found = 0;
	if (look_for_cmd(&cmd, line, &found, "pwd"))
	{
		ft_pwd(STDOUT_FILENO);
	}
	if (look_for_cmd(&cmd, line, &found, "exit"))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (look_for_cmd(&cmd, line, &found, "cd "))
		ft_change_dir(cmd);
	if (look_for_cmd(&cmd, line, &found, "env"))
	{
		ft_put_env(*env, 1);
	}
	if (look_for_cmd(&cmd, line, &found, "echo -n "))
	{
		ft_echo(cmd, 1, 1);
	}
	else if (look_for_cmd(&cmd, line, &found, "echo "))
	{
		ft_echo(cmd, 0, 1);
	}
	if (look_for_cmd(&cmd, line, &found, "export "))
		ft_export(env, line + 7, 1);
	else if (look_for_cmd(&cmd, line, &found, "export"))
		ft_export(env, 0, 1);
	if (look_for_cmd(&cmd, line, &found, "unset"))
		ft_unset(env, line + 5, 1);
	return (found);
}
