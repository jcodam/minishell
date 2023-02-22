/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   what_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:03:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/22 17:38:09 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	look_for_cmd(char *line, int *found, char *commend)
{
	char	*cmd = 0;
	cmd = ft_strnstr(line, commend, 9);
	if (!cmd)
		return (0);
	*found += 1;
	return (1);
}

static char **mkarg(char *line)
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
	// ft_putarrs_fd(args, 1);
	return (args);
}

int	what_cmd1(char *line, t_super *super, int pipes, int fd)
{
	int		found;
	char	**args;

	found = 0;
	args = mkarg(line);
	if (look_for_cmd(*args, &found, "$?") && ft_arrlen_c(args) == 1)
	{
		printf("%d\n", super->exit_code);
	}
	super->exit_code = 0;
	if (look_for_cmd(*args, &found, "pwd"))
	{
		ft_pwd(super, fd);
	}
	else if (look_for_cmd(*args, &found, "exit"))
		ft_exit_builtin(args, super);
	else if (look_for_cmd(*args, &found, "cd"))
		ft_change_dir(args[1]);
	else if (look_for_cmd(*args, &found, "env"))
	{
		ft_put_env(super, fd);
	}
	else if (look_for_cmd(*args, &found, "echo"))
	{
		ft_echo(args + 1, fd);
	}
	else if (look_for_cmd(*args, &found, "export"))
		ft_export(super, args, fd);
	else if (look_for_cmd(*args, &found, "unset"))
		ft_unset(super, args, fd);
	else if (look_for_cmd(*args, &found, "var") && ft_arrlen_c(args) == 2)
		printf("%s\n", ft_getvar(args[1], super->env));
	else if (look_for_cmd(*args, &found, "lll"))
		printf("%s\n", ft_replacevar(ft_strdup(line), 3, super->env));
	else
		ft_othercmd(args, super, pipes, fd);
	ft_arrclear_c(args, ft_arrlen_c(args));
	return (found);
}

int ll(char *line)
{
	while (*line && ft_iswhite_space(*line))
		line++;
	if (*line)
		return (1);
	return (0);
}

static char **m_arg(char *line, int *p)
{
	char	**args;
	int		j = 0;

	args = ft_split(line, '|');
	ft_putarrs_fd(args, 1);
	while (args[j])
	{
		if (!ll(args[j]))
			args = ft_arrdell_index(args, j, free);
		else
			j++;
	}
	ft_putarrs_fd(args, 1);
	*p = j;
	return (args);
}

int	what_cmd(char *line, t_super *super)
{
	// printf("%s\n", line);
	return (what_cmd1(line, super, 0, 1));
}
int	what_cmd2(char *line, t_super *super)
{
	int	pipes;

	pipes = 0;
	m_arg(line, &pipes);
	printf("%d\n", pipes);
	return (super->exit_code);
}
