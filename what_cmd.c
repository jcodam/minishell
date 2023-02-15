/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   what_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:03:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/15 17:57:41 by jbax          ########   odam.nl         */
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

char **mkarg(char *line)
{
	char	**args;
	int		i = 0;
	char	*temp;

	args = malloc(1 * sizeof(char *));
	args[0] = 0;
	temp = singlearg(line, &i);
	while (temp)
	{
		if (*temp)
			args = ft_arradd_index(args, temp, 100);
		temp = singlearg(line, &i);
	}
	ft_putarrs_fd(args, 1);
	return (args);
}

int	what_cmd(char *line, t_super *super)
{
	int		found;
	char	*cmd;
	char	**args;

	found = 0;
	args = mkarg(line);
	if (look_for_cmd(&cmd, line, &found, "$?") && ft_arrlen_c(args) == 1)
	{
		printf("%d\n", super->exit_code);
	}
	super->exit_code = 0;
	if (look_for_cmd(&cmd, line, &found, "pwd"))
	{
		ft_pwd(super, STDOUT_FILENO);
	}
	else if (look_for_cmd(&cmd, line, &found, "exit"))
		ft_exit_builtin(args, super);
	else if (look_for_cmd(&cmd, line, &found, "cd "))
		ft_change_dir(cmd);
	else if (look_for_cmd(&cmd, line, &found, "env"))
	{
		ft_put_env(super, 1);
	}
	else if (look_for_cmd(&cmd, line, &found, "echo -n "))
	{
		ft_echo(cmd, 1, 1);
	}
	else if (look_for_cmd(&cmd, line, &found, "echo "))
	{
		ft_echo(cmd, 0, 1);
	}
	else if (look_for_cmd(&cmd, line, &found, "export "))
		ft_export(super, args, 1);
	else if (look_for_cmd(&cmd, line, &found, "export"))
		ft_export(super, 0, 1);
	else if (look_for_cmd(&cmd, line, &found, "unset"))
		ft_unset(super, args, 1);
	else if (look_for_cmd(&cmd, line, &found, "var") && ft_arrlen_c(args) == 2)
		printf("%s\n", ft_getvar(args[1], super->env));
	else
		ft_othercmd(args, super, 0);
	ft_arrclear_c(args, ft_arrlen_c(args));
	return (found);
}
