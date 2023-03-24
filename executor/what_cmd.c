/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   what_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:03:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/24 20:29:17 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

static int	look_for_cmd(char *line, int *found, char *commend)
{
	char	*cmd;

	cmd = ft_strnstr(line, commend, 9);
	if (!cmd)
		return (0);
	*found += 1;
	return (1);
}

static char	**mkarg(char *line)
{
	char	**args;
	int		i;
	char	*temp;

	i = 0;
	args = malloc(1 * sizeof(char *));
	args[0] = 0;
	temp = singlearg(line, &i);
	while (temp)
	{
		if (*temp)
			args = ft_arradd_index(args, temp, 100);
		temp = singlearg(line, &i);
	}
	return (args);
}

static int	lookcmd(char **args, t_super *super, int *found, int fd)
{
	if (look_for_cmd(*args, found, "pwd"))
		ft_pwd(fd);
	else if (look_for_cmd(*args, found, "exit"))
		ft_exit_builtin(args);
	else if (look_for_cmd(*args, found, "cd"))
		ft_change_dir(args[1]);
	else if (look_for_cmd(*args, found, "env"))
		ft_put_env(super, fd);
	else if (look_for_cmd(*args, found, "echo"))
		ft_echo(args + 1, fd);
	else if (look_for_cmd(*args, found, "export"))
		ft_export(super, args, fd);
	else if (look_for_cmd(*args, found, "unset"))
		ft_unset(super, args);
	return (0);
}

int	what_cmd1(char *line, t_super *super, int pipes, int fd)
{
	int		found;
	char	**args;

	found = 0;
	tmpfileswitch(&line);
	if (!line || !*line)
		return 0;
	args = mkarg(line);
	if (look_for_cmd(*args, &found, "$?") && ft_arrlen_c(args) == 1)
	{
		printf("%d\n", g_exit_code);
		g_exit_code = 0;
		return (0);
	}
	g_exit_code = 0;
	lookcmd(args, super, &found, fd);
	if (!found && look_for_cmd(*args, &found, "var") && ft_arrlen_c(args) == 2)
		printf("%s\n", ft_getvar(args[1], super->env));
	else if (look_for_cmd(*args, &found, "lll"))
		printf("%s\n", ft_replacevar(ft_strdup(line), 3, super->env));
	else if (!found)
		ft_othercmd(args, super, pipes, fd);
	ft_arrclear_c(args, ft_arrlen_c(args));
	return (found);
}
