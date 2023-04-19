/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   what_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:03:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/19 17:07:02 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	stage_files(char **files, int *tokens)
{
	int	index;

	index = 0;
	while (files && files[index])
	{
		if (tokens[index] == REDIRECT_IP || tokens[index] == RD_TIL_DELIM)
			setfd_read(files[index]);
		else if (tokens[index] == REDIRECT_OP)
			setfd_write(files[index]);
		else if (tokens[index] == REDIRECT_APPEND)
			setfd_append(files[index]);
		index++;
	}
	return (0);
}

static int	look_for_cmd(char *line, int *found, char *commend)
{
	char	*cmd;
	int		i;

	i = ft_strncmp(line, commend, strlen(line));
	if (i)
		return (0);
	cmd = ft_strnstr(line, commend, strlen(commend));
	if (!cmd)
		return (0);
	*found += 1;
	return (1);
}

// static char	**mkarg(char *line)
// {
// 	char	**args;
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	args = malloc(1 * sizeof(char *));
// 	args[0] = 0;
// 	temp = singlearg(line, &i);
// 	while (temp)
// 	{
// 		if (*temp)
// 			args = ft_arradd_index(args, temp, 100);
// 		temp = singlearg(line, &i);
// 	}
// 	return (args);
// }

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

int	what_cmd3(char **args, t_super *super, int pipes, int fd)
{
	int	found;

	found = 0;
	if (!args || !*args)
		return (1);
	if (look_for_cmd(*args, &found, "$?") && ft_arrlen_c(args) == 1)
	{
		printf("%d\n", g_exit_code);
		g_exit_code = 0;
		return (0);
	}
	g_exit_code = 0;
	lookcmd(args, super, &found, fd);
	if (!found)
		ft_othercmd(args, super, pipes, fd);
	return (found);
}

	// ft_putarrs_fd(bigdata->args, 1);
	// ft_putarrs_fd(bigdata->files, 1);
int	what_cmd1(t_tokens *bigdata, t_super *super, int pipes)
{
	print_all_tokens(bigdata);
	bigdata->args = arr_expander(bigdata->args, super->env, 0);
	if (bigdata->files)
	{
		bigdata->files = arr_expander(bigdata->files, super->env, 1);
		if (!bigdata->files)
			return (1);
	}
	stage_files(bigdata->files, bigdata->mini_tok);
	return (what_cmd3(bigdata->args, super, pipes, 1));

}

	// if (!found && look_for_cmd(*args, &found, "var") 
	// && ft_arrlen_c(args) == 2)
	// 	printf("%s\n", ft_getvar(args[1], super->env));
	// else if (look_for_cmd(*args, &found, "lll"))
	// 	printf("%s\n", ft_replacevar(ft_strdup(line), 3, super->env));
	// ft_arrclear_c(args, ft_arrlen_c(args));
